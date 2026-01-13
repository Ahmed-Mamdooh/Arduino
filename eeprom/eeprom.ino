#include <EEPROM.h>
#define PTN A1
#define LED 11

int maxFade = 255;

void setup() {
  pinMode(PTN, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  
  // Read initial value from EEPROM
  maxFade = EEPROM.read(0);
  Serial.print("Initial maxFade: ");
  Serial.println(maxFade);
}

void loop() {
  if (Serial.available() > 0) {
    int data = Serial.parseInt();
    // Use data > 0 to avoid saving '0' if parseInt times out
    if (data > 0 && data <= 255) {
      maxFade = data;
      EEPROM.update(0, maxFade);
      Serial.print("Updated maxFade to: ");
      Serial.println(maxFade);
    }
  }

  // Calculate fade
  // Note: 1023.0 ensures floating point math is used
  int fadePercentage = analogRead(PTN) / 4;
  if(maxFade < fadePercentage) fadePercentage = maxFade;

  // Apply to LED
  analogWrite(LED, fadePercentage);
}