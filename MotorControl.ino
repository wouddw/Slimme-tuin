#include "Pomp.h"

// Maak een pomp-object aan
Pomp mijnPomp;

void setup() {
    Serial.begin(115200);           // Start seriële communicatie
    while (!Serial);                // Wacht tot seriële verbinding actief is (ESP32-specifiek)

    Serial.println("Slimme serre pomp");
    Serial.println("Typ een commando: start, stop, run <milliseconden>");
}

void loop() {
    // Controleer of er seriële input is
    if (Serial.available()) {
        String invoer = Serial.readStringUntil('\n');  // Lees de ingevoerde tekst
        invoer.trim();                                 // Verwijder spaties en enter


        // Verwerk commando’s
        if (invoer == "start") {
            mijnPomp.start();                          // Zet pomp aan
        } 
        else if (invoer == "stop") {
            mijnPomp.stop();                           // Zet pomp uit
        } 


        else if (invoer.startsWith("run ")) {
            String tijdString = invoer.substring(4);              // Haal tijd uit commando
            unsigned long duur = tijdString.toInt();              // Zet om naar getal

            if (duur > 0) {
                mijnPomp.draaiVoor(duur);                          // Laat pomp draaien
            } 
            else {
                Serial.println("Ongeldige tijdsduur.");            // Foutmelding bij ongeldig getal
            }
        } 
        else {
            Serial.println("kan niet, gebruik: start, stop of run <ms>");
        }
    }
}
