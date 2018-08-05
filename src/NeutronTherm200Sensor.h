#ifndef NEUTRON_Therm200_SENSOR_H
#define NEUTRON_Therm200_SENSOR_H

#include "NeutronSensor.h"

class NeutronTherm200Sensor : public NeutronSensor {
    public:
        NeutronTherm200Sensor(int pin, String name);
        ~NeutronTherm200Sensor();
        String readSensor();
};

#endif
