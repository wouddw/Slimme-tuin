#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include <string>

class Actuator {
private:
    // Pump config
    const int POMP_PIN = 19;
    bool pompStatus;
    
    // RGB LED pins
    const int ROOD_PIN = 26;
    const int GROEN_PIN = 27;
    const int BLAUW_PIN = 25;

public:
    // default contstructor
    Actuator();
    void begin();
    
    // Pump functions, start, stop draaiVoor
    void start_pomp();
    void stop_pomp();
    void draaiVoor_pomp(int seconden); // run pump for x seconds
    
    // LED functions
    void led_aan(std::string kleur); // turn LED on red, green, yellow
    void led_uit();                  // turn all the LED's off

    bool isPompActief();  // Geeft true terug als pomp actief is

};

#endif
