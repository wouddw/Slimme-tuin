#include "Actuator.h"

Actuator::Actuator() : pompStatus(false) {}

void Actuator::begin() {
    // Initialiseer pomp
    pinMode(POMP_PIN, OUTPUT);
    stop_pomp();
    
    // Initialiseer RGB LED
    pinMode(ROOD_PIN, OUTPUT);
    pinMode(GROEN_PIN, OUTPUT);
    pinMode(BLAUW_PIN, OUTPUT);
    led_uit();
}

// Pomp functies
void Actuator::start_pomp() {
    digitalWrite(POMP_PIN, HIGH);
    pompStatus = true;
}

void Actuator::stop_pomp() {
    digitalWrite(POMP_PIN, LOW);
    pompStatus = false;
}

void Actuator::draaiVoor_pomp(int seconden) {
    start_pomp();
    delay(seconden * 1000);
    stop_pomp();
}

// RGB LED functies (gemeenschappelijke kathode)
void Actuator::led_aan(std::string kleur) {
    // Converteer naar lowercase
    for (char &c : kleur) c = tolower(c);
    
    led_uit(); // Eerst alle kleuren uitzetten
    
    if (kleur == "rood") {
        digitalWrite(ROOD_PIN, LOW);
         digitalWrite(BLAUW_PIN, HIGH);
          digitalWrite(GROEN_PIN, HIGH);
        ;
    } 
    else if (kleur == "groen") {
        digitalWrite(GROEN_PIN, LOW);
        digitalWrite(BLAUW_PIN, HIGH);
        digitalWrite(ROOD_PIN, HIGH);
    }
    else if (kleur == "geel") {
        digitalWrite(ROOD_PIN, LOW);
        digitalWrite(GROEN_PIN, LOW);
        digitalWrite(BLAUW_PIN, HIGH);
    }
}

void Actuator::led_uit() {
    digitalWrite(ROOD_PIN, HIGH);
    digitalWrite(GROEN_PIN, HIGH);
    digitalWrite(BLAUW_PIN, HIGH);
}