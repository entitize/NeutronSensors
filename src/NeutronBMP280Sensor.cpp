#include "NeutronBMP280Sensor.h"

NeutronBMP280Sensor::NeutronBMP280Sensor(String name): NeutronSensor(0, name) {
    bmp = new Adafruit_BMP280();
    bmp->begin();
};

String NeutronBMP280Sensor::readSensor() {
    float temperature = bmp->readTemperature();
    float pressure = bmp->readPressure();

    return String(temperature) + ":" + String(pressure);

};

NeutronBMP280Sensor::~NeutronBMP280Sensor() {

}
