#ifndef POMP_H
#define POMP_H

#include <Arduino.h>

// Klasse die een simpele waterpomp voorstelt
class Pomp {
private:
    bool status;                  // Huidige status van de pomp (aan of uit)
    const int controlePin = 19;   // Vaste pin voor de pomp (GPIO 19)

public:
    Pomp();  // Constructor

    int geefPin() const;                          // Geeft de pin terug (altijd 19)
    void start_pomp();                                 // Zet de pomp aan
    void stop_pomp();                                  // Zet de pomp uit
    void draaiVoor_pomp(unsigned long duurMillis);     // Laat de pomp draaien voor X milliseconden
};

#endif
