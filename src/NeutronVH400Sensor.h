#ifndef NEUTRON_VH400_SENSOR_H
#define NEUTRON_VH400_SENSOR_H

#include "NeutronSensor.h"

class NeutronVH400Sensor : public NeutronSensor {
    public:
        NeutronVH400Sensor(int pin, String name);
        ~NeutronVH400Sensor();
        String readSensor();
};

#endif
