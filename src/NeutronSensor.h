#ifndef NeutronSensor_H
#define NeutronSensor_H

#include "OneWire.h"
#include "lib-dallas-temp.h"

#ifndef MAX_SENSORS
#define MAX_SENSORS 4
#endif


class NeutronSensor
{
    public:

        NeutronSensor(int pin);
        ~NeutronSensor();

        //Read sensor
        virtual double readSensor() = 0;

        // Number of initialized sensors
        static int totalSensors;

    protected:

        String name;

        int pin;
        int type;

};

#endif
