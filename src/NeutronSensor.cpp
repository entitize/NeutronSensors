#include "NeutronSensor.h"

int NeutronSensor::totalSensors = 0;

//Base Neutron Sensor
NeutronSensor::NeutronSensor(int pin, String name): pin(pin), name(name) {
    totalSensors += 1;
};

NeutronSensor::~NeutronSensor() {

}
