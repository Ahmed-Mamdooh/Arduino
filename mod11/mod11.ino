#define LED_1_PIN 11
#define LED_2_PIN 10

unsigned long previousTimeLED1Blink = millis();
unsigned long timeIntervalLED1Blink = 600;

unsigned long previousTimeLED2Blink = millis();
unsigned long timeIntervalLED2Blink = 150;

int LED1State = LOW;
int LED2State = LOW;

void setup() {
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
}

void loop() {
  unsigned long timeNow = millis();

  // LED 1 Logic
  if (timeNow - previousTimeLED1Blink >= timeIntervalLED1Blink) {
    LED1State = !LED1State; // Simplified toggle
    digitalWrite(LED_1_PIN, LED1State);
    previousTimeLED1Blink = timeNow; // Reset the timer
  }

  // LED 2 Logic (Moved outside of the LED 1 bracket)
  if (timeNow - previousTimeLED2Blink >= timeIntervalLED2Blink) {
    LED2State = !LED2State; // Simplified toggle
    digitalWrite(LED_2_PIN, LED2State);
    previousTimeLED2Blink = timeNow; // Reset the timer
  }
}