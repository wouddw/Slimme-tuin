#include "Actuator.h"

Actuator actuator;

void setup() {
    actuator.begin(); // init alles (leds + pomp)
    Serial.begin(9600); // serial monitor aanzetten om status te tonen
}

void loop() {
    // LED voorbeelden
    actuator.led_aan("rood");  // rood aan
    delay(1000);

    actuator.led_aan("groen"); // groen aan
    delay(1000);

    actuator.led_aan("geel");  // geel = rood + groen
    delay(1000);

    actuator.led_uit();        // alles uit
    delay(500);

    // Pomp starten
    actuator.start_pomp();     
    delay(2000);

    // Checken of pomp actief is
    if (actuator.isPompActief()) {
        Serial.println("Pomp is AAN");
    } else {
        Serial.println("Pomp is UIT");
    }

    actuator.stop_pomp();      
    delay(500);

    // pomp draaien voor 3 seconden
    actuator.draaiVoor_pomp(3); 
    delay(1000);
}
