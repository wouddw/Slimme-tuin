#include "Sensor.h"

Sensor sensor; //maak een object van de Sensor klasse

void setup() {
    Serial.begin(115200); //start communicatie tussen esp32 en computer
    sensor.begin(); //initialiseer de sensor
}

void loop() {
    float temperatuur = sensor.getTemperatuur(); //zet de waarde van 'getTemperatuur' om in een float in 'temperatuur'
    float luchtvochtigheid = sensor.getLuchtvochtigheid(); //zet de waarde van 'getLuchtvochtigheid' om in een float in 'luchtvochtigheid'
    int bodemvochtigheid = sensor.getBodemvochtigheid(); //zet de waarde van 'getBodemvochtigheid' om in een int in 'bodemvochtigheid'

    delay(2000); // wacht 2 seconden tussen metingen
}