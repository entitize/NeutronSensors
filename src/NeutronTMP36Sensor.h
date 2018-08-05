#ifndef NEUTRON_TMP36_SENSOR_H
#define NEUTRON_TMP36_SENSOR_H

#include "NeutronSensor.h"

// Fake sensor that returns readings from 1 - 100

class NeutronTMP36Sensor : public NeutronSensor {
    public:
        NeutronTMP36Sensor(int pin, String name);
        ~NeutronTMP36Sensor();
        String readSensor();
};

#endif
