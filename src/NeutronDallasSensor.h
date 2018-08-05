#ifndef NEUTRON_DALLAS_SENSOR_H
#define NEUTRON_DALLAS_SENSOR_H

#include "NeutronSensor.h"

class NeutronDallasSensor : public NeutronSensor {
    public:
        NeutronDallasSensor(int pin, String name);
        ~NeutronDallasSensor();
        String readSensor();

        OneWire* oneWire;
        DallasTemperature* sensor;

};

#endif
