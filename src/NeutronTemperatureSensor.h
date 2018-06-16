#ifndef NEUTRON_TEMPERATURE_SENSOR_H
#define NEUTRON_TEMPERATURE_SENSOR_H

#include "NeutronSensor.h"

class NeutronTemperatureSensor : public NeutronSensor {
    public:
        NeutronTemperatureSensor(int pin, String name);
        ~NeutronTemperatureSensor();
        String readSensor();

        OneWire* oneWire;
        DallasTemperature* sensor;

};

#endif
