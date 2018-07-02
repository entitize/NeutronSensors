#ifndef NEUTRON_UV_SENSOR_H
#define NEUTRON_UV_SENSOR_H

#include "NeutronSensor.h"

class NeutronUVSensor : public NeutronSensor {
    public:
        NeutronUVSensor(String name);
        ~NeutronUVSensor();
        String readSensor();

        Adafruit_SI1145* sensor;
};

#endif
