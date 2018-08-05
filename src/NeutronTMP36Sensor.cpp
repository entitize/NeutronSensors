#include "NeutronTMP36Sensor.h"

NeutronTMP36Sensor::NeutronTMP36Sensor(int pin, String name): NeutronSensor(pin, name) {

};

String NeutronTMP36Sensor::readSensor() {

  int reading = analogRead(pin);

  float voltage = reading * 3.3;
  voltage /= 4096;

  float temperatureC = (voltage - 0.5) * 100;
  return String(temperatureC);
}

NeutronTMP36Sensor::~NeutronTMP36Sensor() {

}
