#include "Actuator.h"

Actuator actuator;


void setup() {
    actuator.begin();
}

void loop() {
    // LED voorbeelden
    actuator.led_aan("rood");
    delay(1000);

    actuator.led_aan("groen");
    delay(1000);

    actuator.led_aan("geel"); // rood + groen
    delay(1000);

    actuator.led_uit();
    delay(500);

    // Pomp voorbeelden
    actuator.start_pomp();
    delay(2000);
    actuator.stop_pomp();
    delay(500);

    actuator.draaiVoor_pomp(3); // 3 seconden
    delay(1000); // Wacht even voor herhaling
}
