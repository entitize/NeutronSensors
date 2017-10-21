#include "NeutronMoistureSensor.h"

NeutronMoistureSensor::NeutronMoistureSensor(int pin): NeutronSensor(pin) {};

double NeutronMoistureSensor::readSensor() {
    double volts = analogRead(pin);
    return volts;
};

NeutronMoistureSensor::~NeutronMoistureSensor() {
    
}
