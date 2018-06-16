#ifndef NEUTRON_DUMMY_SENSOR_H
#define NEUTRON_DUMMY_SENSOR_H

#include "NeutronSensor.h"

// Fake sensor that returns readings from 1 - 100

class NeutronDummySensor : public NeutronSensor {
    public:
        NeutronDummySensor(int pin, String name);
        ~NeutronDummySensor();
        String readSensor();
};

#endif
