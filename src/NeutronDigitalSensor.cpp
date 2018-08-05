#include "NeutronDigitalSensor.h"

NeutronDigitalSensor::NeutronDigitalSensor(int pin, String name): NeutronSensor(pin, name) {
  pinMode(pin, OUTPUT);
};

String NeutronDigitalSensor::readSensor() {
    double volts = digitalRead(pin);
    return String(volts);
};

NeutronDigitalSensor::~NeutronDigitalSensor() {

}
