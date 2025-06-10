#include "Actuator.h"

void Actuator::begin() {
    pinMode(pompPin, OUTPUT);
    pinMode(ROOD_PIN, OUTPUT);
    pinMode(GROEN_PIN, OUTPUT);
    pinMode(BLAUW_PIN, OUTPUT);
    led_uit();
    stop_pomp();
}

void Actuator::start_pomp() {
    digitalWrite(pompPin, HIGH);
    pompHandmatig = true;
}

void Actuator::stop_pomp() {
    digitalWrite(pompPin, LOW);
    pompHandmatig = false;
    pompDraait = false;
}

void Actuator::draaiVoor_pomp(int seconden) {
    if (!pompHandmatig) {
        digitalWrite(pompPin, HIGH);
        pompDraait = true;
        pompStartTijd = millis();
        pompDuur = seconden * 1000;
    }
}

void Actuator::update() {
    if (pompDraait && !pompHandmatig && (millis() - pompStartTijd >= pompDuur)) {
        digitalWrite(pompPin, LOW);
        pompDraait = false;
    }
}

void Actuator::led_aan(String kleur) {
    led_uit();  // eerst alles uitzetten
    if (kleur == "rood") digitalWrite(ROOD_PIN, LOW);
    else if (kleur == "groen") digitalWrite(GROEN_PIN, LOW);
    else if (kleur == "blauw") digitalWrite(BLAUW_PIN, LOW);
}

void Actuator::led_uit() {
    digitalWrite(ROOD_PIN, HIGH);
    digitalWrite(GROEN_PIN, HIGH);
    digitalWrite(BLAUW_PIN, HIGH);
}

bool Actuator::isPompActief() {
    return pompDraait || pompHandmatig;
}