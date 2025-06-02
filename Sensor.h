#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_AHTX0.h>

class Sensor {
private:
    Adafruit_AHTX0 aht; //een object van de klasse Adafruit_AHTX0 uit de Adafruit bibliotheek
    sensors_event_t temp; //opslag van temperatuur
    sensors_event_t humidity; //opslag van luchtvochtigheid
public: 
    void begin(); //initialiseer sensor
    float getTemperatuur(); //temperatuur 'getten'
    float getLuchtvochtigheid(); //luchtvochtigheid 'getten'
};
#endif
