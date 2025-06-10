# 🌱 Slimme Tuin Project met ESP32

Een IoT-dashboard voor het monitoren en beheren van een geautomatiseerde slimme tuin. Het systeem maakt gebruik van een **ESP32**, diverse **sensoren**, en **actuatoren** om de tuin te bewaken, te irrigeren, en de gebruiker te informeren via een webinterface.

---

## 📋 Inhoudsopgave

1. [Projectbeschrijving](#projectbeschrijving)  
2. [Hardware](#hardware-benodigdheden)  
3. [Softwarestructuur](#softwarestructuur)  
4. [Bestandstructuur](#bestandstructuur)  
5. [Installatie](#installatie)  
6. [Functionaliteiten](#functionaliteiten)  
7. [Belangrijke aandachtspunten](#belangrijke-aandachtspunten)  
8. [Mogelijke uitbreidingen](#mogelijke-uitbreidingen)  
9. [Auteurs](#auteurs)

---

## 📌 Projectbeschrijving

Het doel van dit project is het bouwen van een zelfregelende tuincontroller op basis van een **ESP32 microcontroller**. De controller leest data van:

- een **AHT10/AHT20-sensor** voor temperatuur en luchtvochtigheid,
- een **bodemvochtigheidssensor**,  

en bestuurt:

- een **pomp** (voor irrigatie),  
- en een **RGB LED**,  

om visuele status aan te geven. Via een **dynamisch webdashboard** kun je live data bekijken, meldingen ontvangen en handmatige acties uitvoeren.

---

## 🔧 Hardware benodigdheden

| Component                     | Aantal |
|------------------------------|--------|
| ESP32 ontwikkelbord          | 1      |
| AHT10/AHT20 sensor (I²C)     | 1      |
| Bodemvochtigheidssensor      | 1      |
| Waterpomp (met relais of transistor) | 1 |
| RGB LED (of 3 enkele LEDs)   | 1 set  |
| Weerstanden (voor LED's)     | 3× 220Ω|
| Pull-up weerstanden voor I²C | 2× 4.7kΩ|
| Breadboard + jumper wires    | -      |

**Aansluitingen:**

| Functie          | Pin ESP32  |
|------------------|------------|
| SDA (I2C)        | GPIO 21    |
| SCL (I2C)        | GPIO 22    |
| Bodemvochtigheid | GPIO 36 (ADC1_CH0) |
| Pomp             | GPIO 5     |
| LED Rood         | GPIO 12    |
| LED Groen        | GPIO 13    |
| LED Blauw        | GPIO 14    |

---

## 🧠 Softwarestructuur

### `Sensor.h / Sensor.cpp`

- Beheert communicatie met de AHT-sensor en analoge sensor.
- `begin()`, `getTemperatuur()`, `getLuchtvochtigheid()`, `getBodemvochtigheid()`

### `Actuator.h / Actuator.cpp`

- Stuurt de pomp en LED's aan.
- Houdt pompstatus bij.
- `start_pomp()`, `stop_pomp()`, `draaiVoor_pomp()`, `update()`, `isPompActief()`

### `main.ino`

- WiFi + webserver configuratie
- Regelmatige updates & dashboard

---

## 🗂 Bestandstructuur

```
SlimmeTuin/
├── Sensor.h
├── Sensor.cpp
├── Actuator.h
├── Actuator.cpp
└── SlimmeTuin.ino
```

---

## 🚀 Installatie

1. Installeer Arduino IDE + ESP32 support
2. Installeer bibliotheken:
   - `Adafruit AHTX0`
   - `Wire` (standaard)
3. Selecteer:
   - Board: ESP32 Dev Module
   - Poort: juiste COM-poort
4. Upload de code naar ESP32
5. Verbind je met hetzelfde WiFi-netwerk

---

## ⚙️ Functionaliteiten

| Onderdeel       | Omschrijving |
|-----------------|--------------|
| 🌡 Sensoruitlezing | Meet elke 5s |
| 🚨 Alarmmeldingen | Log bij overschrijding |
| 💧 Pompbesturing  | Automatisch / handmatig |
| 🔵 LED-status     | Rood, blauw of groen |
| 🌐 Webinterface   | HTML-dashboard |
| 🧾 Logboek        | Tijdlijn met acties |
| 📊 Pompstatus     | AAN of UIT-indicator |

---

## ❗ Belangrijke aandachtspunten

- Correcte I2C-aansluitingen
- Pull-up weerstanden op SDA/SCL
- Let op foutmeldingen zoals `i2c_master timeout`

---

## 🌟 Mogelijke uitbreidingen

- AJAX dashboard met live updates
- Data loggen op SD of in cloud
- Notificaties via Telegram of e-mail
- Sensoren voor licht, regen, temperatuur buiten

---

## 👨‍💻 Auteurs

| Naam                   | Rol                       |
|------------------------|---------------------------|
| **Woud De Waegenaere** | Sensor-klasse & meetlogica |
| **Lars Ysebaert**      | Actuator-klasse & pomp/LED-besturing |
| **Vincent Junior Goemaere**                | Integratie, webinterface, test & debug |

---

## 📝 Licentie

MIT License – Vrij te gebruiken en aan te passen.