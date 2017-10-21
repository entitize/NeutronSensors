#ifndef NEUTRON_MOISTURE_SENSOR_H
#define NEUTRON_MOISTURE_SENSOR_H

#include "NeutronSensor.h"

class NeutronMoistureSensor : public NeutronSensor {
    public:
        NeutronMoistureSensor(int pin);
        ~NeutronMoistureSensor();
        double readSensor();
};

#endif