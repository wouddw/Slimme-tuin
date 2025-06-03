#include "Actuator.h"

// default constructor, pump status to false
Actuator::Actuator() : pompStatus(false) {}

void Actuator::begin() {
    // set pump pin as output
    pinMode(POMP_PIN, OUTPUT);
    stop_pomp(); // setting pump of at the start
    
    // setting RGB LED pins as output
    pinMode(ROOD_PIN, OUTPUT);
    pinMode(GROEN_PIN, OUTPUT);
    pinMode(BLAUW_PIN, OUTPUT);
    led_uit(); // turn all LEDs off at the beginning
}



// pump
void Actuator::start_pomp() {           // Member function of the Actuator class that starts the pump
    digitalWrite(POMP_PIN, HIGH);       // turn pump on by setting the pin HIGH
    pompStatus = true;                  // Update the internal status variable to indicate the pump is running
}

void Actuator::stop_pomp() {            // Member function of the Actuator class that stops the pump
    digitalWrite(POMP_PIN, LOW);        // turn pump off
    pompStatus = false;                 // Update the internal status variable to indicate the pump is running
}

void Actuator::draaiVoor_pomp(int seconden) {   // Member function of the Actuator class that sets a time for the pump to run for
    start_pomp();                               // turn pump on
    delay(seconden * 1000);                     // wait x seconds
    stop_pomp();                                // turn pump off again
}

bool Actuator::isPompActief() {
    return pompStatus;
    }



// RGB
// common cathode RGB, LOW is ON

void Actuator::led_aan(std::string kleur) {
    // make the string lowercase
    for (char &c : kleur) c = tolower(c);
    
    led_uit(); // always turn everything off first

    if (kleur == "rood") {
        digitalWrite(ROOD_PIN, LOW);   // red ON
        digitalWrite(BLAUW_PIN, HIGH); // others OFF
        digitalWrite(GROEN_PIN, HIGH);
    } 
    else if (kleur == "groen") {
        digitalWrite(GROEN_PIN, LOW);  // green ON
        digitalWrite(BLAUW_PIN, HIGH);
        digitalWrite(ROOD_PIN, HIGH);
    }
    else if (kleur == "geel") {
        digitalWrite(ROOD_PIN, LOW);   // red + green = yellow
        digitalWrite(GROEN_PIN, LOW);
        digitalWrite(BLAUW_PIN, HIGH);
    }
}

void Actuator::led_uit() {
    // turning off, setting all pins to HIGH
    digitalWrite(ROOD_PIN, HIGH);
    digitalWrite(GROEN_PIN, HIGH);
    digitalWrite(BLAUW_PIN, HIGH);
}