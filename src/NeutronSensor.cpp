#include "NeutronSensor.h"

int NeutronSensor::totalSensors = 0;

//Base Neutron Sensor
NeutronSensor::NeutronSensor(int pin): pin(pin) {
    totalSensors += 1;
};

NeutronSensor::~NeutronSensor() {

}
