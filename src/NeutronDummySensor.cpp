#include "NeutronDummySensor.h"

NeutronDummySensor::NeutronDummySensor(int pin, String name): NeutronSensor(pin, name) {

};

String NeutronDummySensor::readSensor() {
    return String(rand() % 100 + 1);
};

NeutronDummySensor::~NeutronDummySensor() {

}
