#include <WiFi.h>
#include <WebServer.h>
#include "Sensor.h" // === File en oprdracht van Woud De Waegenaere ===
#include "Actuator.h" // === File en oprdracht van Lars Ysebaert ===

Sensor sensor;
Actuator actuator;

// === WiFi-instellingen ===
const char* ssid = "VTI-Guest";
const char* password = "Wifi0104";

// === Webserver op poort 80 ===
WebServer server(80);

// === Simulatie van sensorwaarden ===
float temperatuur = 22.3;
float luchtvochtigheid = 57.2;
float bodemvochtigheid = 35.0;

// === Logboek en alarmvariabelen ===
#define MAX_LOGS 20
String logboek[MAX_LOGS];
int logIndex = 0;

bool alarmTemp = false;
bool alarmLucht = false;
bool alarmBodem = false;

// === HTML-pagina met CSS en placeholders ===
String pagina = R"rawliteral(
<!DOCTYPE html><html>
<head>
  <title>Slimme Tuin</title>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
    }
    body {
      font-family: 'Segoe UI', sans-serif;
      background-color: #f4fff3;
      color: #333;
      display: flex;
      min-height: 100vh;
    }
    .main {
      flex: 3;
      padding: 2rem;
      display: flex;
      flex-direction: column;
      gap: 2rem;
    }
    .title {
      font-size: 2rem;
      color: #2e8b57;
      font-weight: bold;
    }
    .sensor-container {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
      gap: 1rem;
    }
    .sensor {
      background-color: #fff;
      border: 2px solid #2e8b57;
      border-radius: 12px;
      padding: 1rem;
      box-shadow: 0 2px 8px rgba(0,0,0,0.05);
      text-align: center;
    }
    .sensor h3 {
      margin-bottom: 0.5rem;
      color: #2e8b57;
    }
    .sensor .value {
      font-size: 1.5rem;
      font-weight: bold;
    }
    .sensor .alarm {
      color: red;
      font-weight: bold;
      margin-top: 0.5rem;
    }
    .buttons {
      text-align: center;
    }
    .buttons button {
      background-color: #2e8b57;
      color: white;
      padding: 0.75rem 1.5rem;
      margin: 0.5rem;
      border: none;
      border-radius: 8px;
      cursor: pointer;
      font-size: 1rem;
      transition: background 0.3s ease;
    }
    .buttons button:hover {
      background-color: #246c46;
    }
    .logboek {
      flex: 1;
      background-color: #fff;
      border-left: 2px solid #2e8b57;
      padding: 1rem;
      overflow-y: auto;
    }
    .logboek h3 {
      color: #2e8b57;
      margin-bottom: 1rem;
    }
    .logboek-entry {
      margin-bottom: 0.5rem;
      font-size: 0.95rem;
      border-bottom: 1px solid #ddd;
      padding-bottom: 0.3rem;
    }
  </style>
</head>
<body>
  <div class="main">
    <div class="title">Slimme Tuin Dashboard</div>

    <div class="sensor-container">
      <div class="sensor">
        <h3>Temperatuur</h3>
        <div class="value">%TEMP% °C</div>
        %ALARM_TEMP%
      </div>
      <div class="sensor">
        <h3>Luchtvochtigheid</h3>
        <div class="value">%LUCHT% %</div>
        %ALARM_LUCHT%
      </div>
      <div class="sensor">
        <h3>Bodemvochtigheid</h3>
        <div class="value">%BODEM% %</div>
        %ALARM_BODEM%
      </div>
    </div>

    <div class="buttons">
      <a href="/pompAan"><button>Pomp Aan</button></a>
      <a href="/pompUit"><button>Pomp Uit</button></a>
      <a href="/ledRood"><button>LED Rood</button></a>
      <a href="/ledGroen"><button>LED Groen</button></a>
    </div>
  </div>

  <div class="logboek">
    <h3>Logboek</h3>
    %LOG%
  </div>
</body>
</html>
)rawliteral";

// === Functie om logregels toe te voegen ===
void voegLogToe(String bericht) {
  if (logIndex >= MAX_LOGS) logIndex = 0;
  logboek[logIndex++] = bericht;
}

// === Processor: vervangt placeholders in HTML ===
String processor(const String& var) {
  if (var == "TEMP") return String(temperatuur, 1);
  if (var == "LUCHT") return String(luchtvochtigheid, 1);
  if (var == "BODEM") return String(bodemvochtigheid, 1);

  if (var == "ALARM_TEMP") return alarmTemp ? "<span class='alarm'>(⚠️ Te warm!)</span>" : "";
  if (var == "ALARM_LUCHT") return alarmLucht ? "<span class='alarm'>(⚠️ Te droog!)</span>" : "";
  if (var == "ALARM_BODEM") return alarmBodem ? "<span class='alarm'>(⚠️ Bodem te droog!)</span>" : "";

  if (var == "LOG") {
    String logHtml = "";
    for (int i = 0; i < MAX_LOGS; i++) {
      if (logboek[i] != "") {
        logHtml += "<div>" + logboek[i] + "</div>";
      }
    }
    return logHtml;
  }

  return "";
}


// === Setup ===
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Verbinding maken met WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nVerbonden! IP: " + WiFi.localIP().toString());

  // === Hoofdpagina met sensorwaarden en alarmen ===
  server.on("/", HTTP_GET, []() {
    // Alarmcheck
    alarmTemp = temperatuur > 30.0;
    alarmLucht = luchtvochtigheid < 40.0;
    alarmBodem = bodemvochtigheid < 30.0;

    if (alarmTemp) voegLogToe("Temperatuur alarm: " + String(temperatuur));
    if (alarmLucht) voegLogToe("Luchtvochtigheid alarm: " + String(luchtvochtigheid));
    if (alarmBodem) voegLogToe("Bodemvochtigheid alarm: " + String(bodemvochtigheid));

    // HTML genereren
    String html = pagina;
    html.replace("%TEMP%", processor("TEMP"));
    html.replace("%LUCHT%", processor("LUCHT"));
    html.replace("%BODEM%", processor("BODEM"));
    html.replace("%ALARM_TEMP%", processor("ALARM_TEMP"));
    html.replace("%ALARM_LUCHT%", processor("ALARM_LUCHT"));
    html.replace("%ALARM_BODEM%", processor("ALARM_BODEM"));
    html.replace("%LOG%", processor("LOG"));
    server.send(200, "text/html", html);
  });

  // === Actieknoppen met logging ===
  server.on("/pompAan", HTTP_GET, []() {
    actuator.start_pomp();
    voegLogToe("Pomp handmatig AAN");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/pompUit", HTTP_GET, []() {
    actuator.stop_pomp();
    voegLogToe("Pomp handmatig UIT");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/ledRood", HTTP_GET, []() {
    actuator.led_aan("rood");
    actuator.led_uit("groen");
    voegLogToe("LED op ROOD gezet");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/ledGroen", HTTP_GET, []() {
    actuator.led_aan("groen");
    actuator.led_uit("rood");
    voegLogToe("LED op GROEN gezet");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
  Serial.println("Webserver gestart!");
}

void loop() {
  server.handleClient();

  static unsigned long vorigeMillis = 0;
  if (millis() - vorigeMillis > 5000) {
    // Sensorwaarden uitlezen
    temperatuur = sensor.getTemperatuur();
    luchtvochtigheid = sensor.getLuchtvochtigheid();
    bodemvochtigheid = sensor.getBodemvochtigheid();

    // === LED-logica ===
    if (bodemvochtigheid < 20 || temperatuur > 35 || luchtvochtigheid > 90) {
      actuator.led_aan("rood");
      actuator.led_uit("groen");
      actuator.led_uit("blauw");
    } else if (bodemvochtigheid < 30 || temperatuur > 30 || luchtvochtigheid > 80) {
      actuator.led_aan("blauw");
      actuator.led_uit("groen");
      actuator.led_uit("rood");
    } else {
      actuator.led_aan("groen");
      actuator.led_uit("rood");
      actuator.led_uit("blauw");
    }

    // === Alleen automatisch pomp starten als hij NIET manueel aanstaat ===
    static bool automatischePompActief = false;
    if (bodemvochtigheid < 30) {
      if (!automatischePompActief) {
        actuator.draaiVoor_pomp(5);  // Draait pomp 5 seconden
        automatischePompActief = true;
        voegLogToe("Pomp automatisch gestart wegens droge bodem");
      }
    } else {
      automatischePompActief = false;  // reset zodat hij later opnieuw mag starten
    }

    vorigeMillis = millis();
  }
}