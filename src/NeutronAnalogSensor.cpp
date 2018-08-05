#include "NeutronAnalogSensor.h"

NeutronAnalogSensor::NeutronAnalogSensor(int pin, String name): NeutronSensor(pin, name) {
  pinMode(pin, OUTPUT);
};

String NeutronAnalogSensor::readSensor() {
    double volts = analogRead(pin);
    return String(volts);
};

NeutronAnalogSensor::~NeutronAnalogSensor() {

}
