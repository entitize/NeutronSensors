#include "NeutronBMP280Sensor.h"

NeutronBMP280Sensor::NeutronBMP280Sensor(String name): NeutronSensor(0, name) {
    sensor = new Adafruit_BMP280();
    sensor->begin();
};

String NeutronBMP280Sensor::readSensor() {
    float temperature = sensor->readTemperature();
    float pressure = sensor->readPressure();

    return String(temperature) + "," + String(pressure);

};

NeutronBMP280Sensor::~NeutronBMP280Sensor() {

}
