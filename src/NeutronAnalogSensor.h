#ifndef NEUTRON_ANALOG_SENSOR_H
#define NEUTRON_ANALOG_SENSOR_H

#include "NeutronSensor.h"

class NeutronAnalogSensor : public NeutronSensor {
    public:
        NeutronAnalogSensor(int pin, String name);
        ~NeutronAnalogSensor();
        String readSensor();
};

#endif
