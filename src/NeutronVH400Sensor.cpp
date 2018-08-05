#include "NeutronVH400Sensor.h"

NeutronVH400Sensor::NeutronVH400Sensor(int pin, String name): NeutronSensor(pin, name) {
    //Initialization
};

NeutronVH400Sensor::~NeutronVH400Sensor() {
    //Deinitialization
};

String NeutronVH400Sensor::readSensor() {

    int analog = analogRead(pin);
    float sensorVoltage = analog*(3.3 / 4096);
    float VWC; //Volumetric Water Content

    //Inputting voltage into piecewise linear functions that model VWC
    //Source: http://vegetronix.com:80/Products/VH400/VH400-Piecewise-Curve.phtml

    if(sensorVoltage <= 1.1) {
        VWC = 10*sensorVoltage-1;
    } else if(sensorVoltage > 1.1 && sensorVoltage <= 1.3) {
        VWC = 25*sensorVoltage-17.5;
    } else if(sensorVoltage > 1.3 && sensorVoltage <= 1.82) {
        VWC = 48.08*sensorVoltage-47.5;
    } else if(sensorVoltage > 1.82) {
        VWC = 26.32*sensorVoltage-7.89;
    }

    return String(VWC);

};
