#include "NeutronDummySensor.h"

NeutronDummySensor::NeutronDummySensor(int pin): NeutronSensor(pin) {

};

double NeutronDummySensor::readSensor() {
    return rand() % 100 + 1;
};

NeutronDummySensor::~NeutronDummySensor() {

}
