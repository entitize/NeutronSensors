#include "NeutronTherm200Sensor.h"

NeutronTherm200Sensor::NeutronTherm200Sensor(int pin, String name): NeutronSensor(pin, name) {
    //Initialization
};

NeutronTherm200Sensor::~NeutronTherm200Sensor() {
    //Deinitialization
};

String NeutronTherm200Sensor::readSensor() {

    int voltage = analogRead(pin)*(3.3 / 4096);
    float temperature = (75.006 * voltage) - 42;
    return String(temperature);

};
