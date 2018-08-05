#ifndef NEUTRON_DIGITAL_SENSOR_H
#define NEUTRON_DIGITAL_SENSOR_H

#include "NeutronSensor.h"

class NeutronDigitalSensor : public NeutronSensor {
    public:
        NeutronDigitalSensor(int pin, String name);
        ~NeutronDigitalSensor();
        String readSensor();
};

#endif
