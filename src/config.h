#ifndef CONFIG_H
#define CONFIG_H

//IMPORTANT:
//All changes here must reflect all changes in webhooks!
//Do not alter any variables here if you do not understand how this project's webhooks work

#define MAX_SENSORS 8
#define PUBLISH_READINGS_EVENT "NE_S_SENDA"
#define GET_CONFIG_EVENT "NE_S_GET_CONFIG"
#define REGISTER_DEVICE_EVENT "NE_S_REGISTER"

#define POWER_PIN 2

#define Z_SENSOR_TYPE_DUMMY 0
#define Z_SENSOR_TYPE_TEMPERATURE 1
#define Z_SENSOR_TYPE_MOISTURE 2
#define Z_SENSOR_TYPE_LIGHT 3
#define Z_SENSOR_TYPE_BMP 4

#define MODE_DELAY 0
#define MODE_LIGHT_SLEEP 1
#define MODE_DEEP_SLEEP 2
#define MODE_STANDBY 3

#define DEFAULT_SLEEP_SECONDS 10

#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)

#define STANDBY_UPDATE_MILLIS (30 * 1000)

#endif
