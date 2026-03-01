#define BTN 7
#define BUZZER 9

void setup() {
  // pinMode is one word; 'pin.Mode' will cause an error
  pinMode(BTN, INPUT);
 
  //pinMode(SOUNDER, OUTPUT);
}

void loop() {
  // Use digitalRead for a button on pin 2
  // Use HIGH instead of ON
  if (digitalRead(BTN) == HIGH) {
    // analogWrite takes the pin as the first argument
    tone(BUZZER, 2000);
  } 
  else {
    noTone(BUZZER);
  }
}