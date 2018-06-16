#include "NeutronMoistureSensor.h"

NeutronMoistureSensor::NeutronMoistureSensor(int pin, String name): NeutronSensor(pin, name) {};

String NeutronMoistureSensor::readSensor() {
    double volts = analogRead(pin);
    return String(volts);
};

NeutronMoistureSensor::~NeutronMoistureSensor() {

}
