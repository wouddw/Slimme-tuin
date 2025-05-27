#include "Pomp.h"

// Constructor: stelt pin in en zorgt dat pomp uit staat bij opstart
Pomp::Pomp()
    : status(false) {
    pinMode(controlePin, OUTPUT);
    digitalWrite(controlePin, LOW);
}

// Geeft de gebruikte pin terug
int Pomp::geefPin() const {
    return controlePin;
}

// Zet de pomp aan
void Pomp::start_pomp() {
    digitalWrite(controlePin, HIGH);
    status = true;
    Serial.println("Pomp is AAN");
}

// Zet de pomp uit
void Pomp::stop_pomp() {
    digitalWrite(controlePin, LOW);
    status = false;
    Serial.println("Pomp is UIT");
}

// Laat de pomp draaien voor een opgegeven tijdsduur
void Pomp::draaiVoor_pomp(unsigned long duurMillis) {
    start();                 // Zet aan
    delay(duurMillis);       // Wacht
    stop();                 // Zet uit
}
