#ifndef NeutronSensor_H
#define NeutronSensor_H

#include "OneWire.h"
#include "lib-dallas-temp.h"
#include <Adafruit_BMP280.h>

#ifndef MAX_SENSORS
#define MAX_SENSORS 4
#endif


class NeutronSensor
{
    public:

        NeutronSensor(int pin, String name);
        ~NeutronSensor();

        //Read sensor
        virtual String readSensor() = 0;

        // Number of initialized sensors
        static int totalSensors;

        String name;

    protected:

        int pin;
        int type;

};

#endif
