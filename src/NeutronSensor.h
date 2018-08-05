#ifndef NeutronSensor_H
#define NeutronSensor_H

//Libraries for the sensors
#include "lib-dallas-temp.h"
#include <Adafruit_BMP280.h>
#include <Adafruit_SI1145.h>
#include "OneWire.h"

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

#include "NeutronDummySensor.h"
#include "NeutronAnalogSensor.h"
#include "NeutronDigitalSensor.h"
#include "NeutronDallasSensor.h"
#include "NeutronBMP280Sensor.h"
#include "NeutronUVSensor.h"
#include "NeutronVH400Sensor.h"
#include "NeutronTherm200Sensor.h"
#include "NeutronTMP36Sensor.h"

#endif
