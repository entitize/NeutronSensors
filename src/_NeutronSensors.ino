/*
 * Project: Neutron Sensors
 * Description: Code for reading and sending temperature sensor data to the cloud
 * Author: Kai Nakamura
 * First Creation Date: 24 July 2017
 * Status: Development
 */
#include "Particle.h"
PRODUCT_ID(5694);
PRODUCT_VERSION(4);

#include "config.h"

#include "SparkJson.h"

#include "NeutronTemperatureSensor.h"
#include "NeutronMoistureSensor.h"
#include "NeutronDummySensor.h"

NeutronSensor* sensors[MAX_SENSORS];

int sleepSeconds;
int sleepMode = -1;
bool recievedConfigUpdate, requestedConfigUpdate = false;

int DEVICE_SEED = random(100000,999999);

void receivedConfigHandler(const char *topic, const char *data);

void setup() {

    Serial.begin(9600);

    pinMode(D0, OUTPUT);

    //Set to Pacific Time Zone
    Time.zone(-7);

    //Subscribe to configuration updates
    Particle.subscribe("hook-response/" + String(GET_CONFIG_EVENT) + String(DEVICE_SEED), receivedConfigHandler, MY_DEVICES);

}

void loop() {

    //Restart the system, if it does not restart correctly
    if (((millis() >= sleepSeconds + 30000) || (millis() >= sleepSeconds + 60000)) && (sleepMode != MODE_DELAY) && (sleepMode != MODE_STANDBY)) {
        System.sleep(SLEEP_MODE_DEEP, 1);
    }

    if (Particle.connected()) {
        if (requestedConfigUpdate) {

            //Wait until we recieve config values
            if (recievedConfigUpdate) {

                readSensorsAndSendData();
                runSleepCycle();

                requestedConfigUpdate = false;
                recievedConfigUpdate = false;
            }

        } else {

            //Send get configuration request
            requestedConfigUpdate = Particle.publish(String(GET_CONFIG_EVENT) + String(DEVICE_SEED), "", PRIVATE, WITH_ACK);
            if (!requestedConfigUpdate) {
                delay(3000);
            }
        }
    }
}

void readSensorsAndSendData() {

    if (photonIsInStandby()) {
        return;
    }

    //Turn on power pin
    digitalWrite(D0, HIGH);

    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    JsonArray& readingsBuffer = jsonBuffer.createArray();

    for (int i = 0; i < NeutronSensor::totalSensors; i++) {
        double reading = sensors[i]->readSensor();
        readingsBuffer.add(reading);
    }

    root["readings"] = readingsBuffer;

    char dataBuffer[1024];
    root.printTo(dataBuffer, sizeof(dataBuffer));
    Particle.publish(String(PUBLISH_READINGS_EVENT) + String(DEVICE_SEED), dataBuffer, PRIVATE, WITH_ACK);

    //Turn off power pin
    digitalWrite(D0, LOW);

}
void runSleepCycle() {

    RGB.control(false);

    if (photonIsInStandby()) {

        //Emit orange
        flashRGB(255, 140, 0);
        delay(STANDBY_UPDATE_MILLIS);

    } else if (sleepMode == MODE_DELAY) {

        delay(sleepSeconds * 1000);

    } else if (sleepMode == MODE_LIGHT_SLEEP) {
        //Light sleep, continues program while Wi-Fi is turned off
        System.sleep(sleepSeconds);

        //Delete delay if you want to run other subroutines while in sleep
        delay(sleepSeconds * 1000);

    } else if (sleepMode == MODE_DEEP_SLEEP) {
        //Deep sleep, everything turned off, starts back from setup()

        System.sleep(SLEEP_MODE_DEEP, sleepSeconds);
    } else {
        //Default safety, delay for 10 seconds
        delay(10000);
    }
}
void deleteSensors() {
    for (int i = 0; i < NeutronSensor::totalSensors; i++) {
        delete sensors[i];
    }

    NeutronSensor::totalSensors = 0;
}

void receivedConfigHandler(const char *topic, const char *data) {

    deleteSensors();

    //Parse JSON containing configuration
	StaticJsonBuffer<2048> jsonBuffer;
	char *mutableCopy = strdup(data);
	JsonObject& root = jsonBuffer.parseObject(mutableCopy);

    if (root.containsKey("settings")) {

        sleepSeconds = atoi(root["settings"]["sleepSeconds"]);
        sleepMode = atoi(root["settings"]["sleepMode"]);

        for (int i = 1; i < MAX_SENSORS + 1; i++) {

            String sensorKey = "s" + String(i);

            if (root.containsKey(sensorKey)) {

                int type = atoi(root[sensorKey]["type"]);
                int pin = atoi(root[sensorKey]["pin"]);

                if (type == SENSOR_TYPE_DUMMY) {
                    sensors[NeutronSensor::totalSensors] = new NeutronDummySensor(pin);
                } else if (type == SENSOR_TYPE_TEMPERATURE) {
                    sensors[NeutronSensor::totalSensors] = new NeutronTemperatureSensor(pin);
                } else if (type == SENSOR_TYPE_MOISTURE) {
                    sensors[NeutronSensor::totalSensors] = new NeutronMoistureSensor(pin);
                } else if (type == SENSOR_TYPE_LIGHT) {
                    sensors[NeutronSensor::totalSensors] = new NeutronMoistureSensor(pin);
                }

            }

        }

    } else {

        //Send Register Device Event
        Particle.publish(String(REGISTER_DEVICE_EVENT));

        while (true) {

            //Emit Blue
            flashRGB(0, 0, 255);
            delay(1000);

            //Emit Green
            flashRGB(0, 255, 0);
            delay(1000);

        }

    }

    free(mutableCopy);

    recievedConfigUpdate = true;

}
void flashRGB(int red, int green, int blue) {

    RGB.control(true);
    RGB.color(red, green, blue);
    RGB.brightness(100);

}
bool photonIsInStandby() {
    return NeutronSensor::totalSensors == 0 || sleepMode == MODE_STANDBY;
}
