#include "Sensor.h"
#include <Wire.h>
#include <Arduino.h>

#define AOUT_PIN 36

void Sensor::begin() {
    Wire.begin(21, 22); //pinnen die worden gebruikt om te communiceren met de sensor (SDA en SCL)
    if (!aht.begin()) { //als verbinding met sensor via I2C niet lukt
        Serial.println("Error"); //print error
    }
}

float Sensor::getTemperatuur(){
    aht.getEvent(&humidity, &temp); //nieuwe meting die in temp en humidity wordt opgeslagen
    return temp.temperature; //geeft de temperatuur als float terug
}

float Sensor::getLuchtvochtigheid(){
    aht.getEvent(&humidity, &temp);
    return humidity.relative_humidity; //geeft de luchtvochtigheid als float terug
}  

int Sensor::getBodemvochtigheid() {
    static bool isInit = false;

    if (!isInit) {
        analogSetAttenuation(ADC_11db);
        isInit = true;
    }

    return analogRead(AOUT_PIN);
}
