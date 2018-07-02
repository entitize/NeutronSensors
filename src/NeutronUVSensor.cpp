#include "NeutronUVSensor.h"

NeutronUVSensor::NeutronUVSensor(String name): NeutronSensor(0, name) {
    sensor = new Adafruit_SI1145();
    sensor->begin();
};

String NeutronUVSensor::readSensor() {
    float visible = sensor->readVisible();
    float ir = sensor->readIR();
    float UVIndex = sensor->readUV() / 100;

    return String(visible) + "," + String(ir) + "," + String(UVIndex);

};

NeutronUVSensor::~NeutronUVSensor() {
    delete sensor;
};
