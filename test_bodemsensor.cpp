#define AOUT_PIN 36 

void setup() {
  Serial.begin(9600);
  analogSetAttenuation(ADC_11db);
}

void loop() {
  int value = analogRead(AOUT_PIN); 

  Serial.print("Moisture value: ");
  Serial.println(value);

  delay(500);
}

