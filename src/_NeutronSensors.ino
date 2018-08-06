/*
 * Project: Neutron Sensors
 * Description: Code for reading and sensor data to the cloud
 * Author: Kai Nakamura
 * First Creation Date: 24 July 2017
 * Last Updated: 5 August 2018
 * Status: Development
 */
#include "Particle.h"
PRODUCT_ID(5694);
PRODUCT_VERSION(5);

#include "config.h"

#include "SparkJson.h"

#include "NeutronSensor.h"

NeutronSensor* sensors[MAX_SENSORS];

int sleepSeconds;
int sleepMode = -1;
bool recievedConfigUpdate, requestedConfigUpdate = false;

int DEVICE_SEED = random(100000,999999);

void receivedConfigHandler(const char *topic, const char *data);

//STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

void setup() {

    Serial.begin(9600);

    pinMode(POWER_PIN, OUTPUT);

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

    String readings = "";

    //Adding sensor readings to JSON object
    for (int i = 0; i < NeutronSensor::totalSensors; i++) {
        String reading = sensors[i]->readSensor();
        readings += reading + ";";
    }

    Particle.publish(String(PUBLISH_READINGS_EVENT) + String(DEVICE_SEED), readings, PRIVATE, WITH_ACK);

    //Turn off power pin
    digitalWrite(POWER_PIN, LOW);

}
void runSleepCycle() {

    RGB.control(false);

    Serial.print("Sleep Seconds: ");
    Serial.println(sleepSeconds);

    Serial.print("Sleep Mode: ");
    Serial.println(sleepMode);

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

    //Parse JSON containing configuration data
	StaticJsonBuffer<2048> jsonBuffer;
	char *mutableCopy = strdup(data);
	JsonObject& root = jsonBuffer.parseObject(mutableCopy);

    if (root.containsKey("settings")) {

        sleepSeconds = atoi(root["settings"]["sleepSeconds"]);
        sleepMode = atoi(root["settings"]["sleepMode"]);

        //Turn on power pin: delay is required between turning power on and activating sensors
        digitalWrite(POWER_PIN, HIGH);
        delay(3000);

        for (int i = 1; i < MAX_SENSORS + 1; i++) {

            String sensorKey = "s" + String(i);

            if (root.containsKey(sensorKey)) {

                int type = atoi(root[sensorKey]["type"]);
                int pin = atoi(root[sensorKey]["pin"]);
                const char* nameArr = root[sensorKey]["name"];
                String name(nameArr);

                if (type == Z_SENSOR_TYPE_DUMMY) {
                    sensors[NeutronSensor::totalSensors] = new NeutronDummySensor(pin, name);
                } else if (type == Z_SENSOR_TYPE_ANALOG) {
                    sensors[NeutronSensor::totalSensors] = new NeutronAnalogSensor(pin, name);
                } else if (type == Z_SENSOR_TYPE_DIGITAL) {
                    sensors[NeutronSensor::totalSensors] = new NeutronDummySensor(pin, name);
                } else if (type == Z_SENSOR_TYPE_DALLAS) {
                    sensors[NeutronSensor::totalSensors] = new NeutronDallasSensor(pin, name);
                } else if (type == Z_SENSOR_TYPE_BMP) {
                    sensors[NeutronSensor::totalSensors] = new NeutronBMP280Sensor(name);
                } else if (type == Z_SENSOR_TYPE_UV) {
                    sensors[NeutronSensor::totalSensors] = new NeutronUVSensor(name);
                } else if (type == Z_SENSOR_TYPE_VH400) {
                    sensors[NeutronSensor::totalSensors] = new NeutronVH400Sensor(pin, name);
                } else if (type == Z_SENSOR_TYPE_THERM200) {
                    sensors[NeutronSensor::totalSensors] = new NeutronTherm200Sensor(pin, name);
                } else if (type == Z_SENSOR_TYPE_TMP36) {
                    sensors[NeutronSensor::totalSensors] = new NeutronTMP36Sensor(pin, name);
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
