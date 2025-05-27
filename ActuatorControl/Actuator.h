#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include <string>

class Actuator {
private:
    // Pomp configuratie
    const int POMP_PIN = 19;
    bool pompStatus;
    
    // RGB LED pinnen
    const int ROOD_PIN = 26;
    const int GROEN_PIN = 27;
    const int BLAUW_PIN = 25;

public:
    Actuator();
    void begin();
    
    // Pomp functies
    void start_pomp();
    void stop_pomp();
    void draaiVoor_pomp(int seconden);
    
    // LED functies
    void led_aan(std::string kleur);
    void led_uit();
};

#endif