#ifndef NEUTRON_BMP280_SENSOR_H
#define NEUTRON_BMP280_SENSOR_H

#include "NeutronSensor.h"

class NeutronBMP280Sensor : public NeutronSensor {
    public:
        NeutronBMP280Sensor(String name);
        ~NeutronBMP280Sensor();
        String readSensor();

        Adafruit_BMP280* sensor;
};

#endif
