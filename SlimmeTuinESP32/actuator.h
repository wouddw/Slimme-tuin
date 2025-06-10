#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

class Actuator {
public:
    void begin();
    void start_pomp();
    void stop_pomp();
    void draaiVoor_pomp(int seconden);
    void update();             // moet in loop() worden aangeroepen
    void led_aan(String kleur);
    void led_uit();
    bool isPompActief();       // status opvragen voor HTML

private:
    const int pompPin = 5;
    const int ROOD_PIN = 12;
    const int GROEN_PIN = 13;
    const int BLAUW_PIN = 14;

    bool pompDraait = false;
    bool pompHandmatig = false;
    unsigned long pompStartTijd = 0;
    unsigned long pompDuur = 0;
};

#endif