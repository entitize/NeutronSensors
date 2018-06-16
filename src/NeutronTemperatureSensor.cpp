#include "NeutronTemperatureSensor.h"

NeutronTemperatureSensor::NeutronTemperatureSensor(int pin, String name): NeutronSensor(pin, name) {
    oneWire = new OneWire(pin);
    sensor = new DallasTemperature(oneWire);

    sensor->begin();
};

NeutronTemperatureSensor::~NeutronTemperatureSensor() {
    delete oneWire;
    delete sensor;
};

String NeutronTemperatureSensor::readSensor() {

    sensor->requestTemperatures();
    double reading = sensor->getTempCByIndex(0);

    int attempts = 0;
    while ((reading <= 0 || reading > 110 || reading == 85) && attempts <= 10) {
        sensor->requestTemperatures();
        reading = sensor->getTempCByIndex(0);
        attempts += 1;
    }
    return String(reading);
};
