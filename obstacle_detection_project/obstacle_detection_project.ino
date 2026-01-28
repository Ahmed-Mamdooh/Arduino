#define  ECHO_PIN 3
#define TRIGGER_PIN 4
#define WARNING_LED_PIN 11

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;


volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile bool newDistanceAvailable = false;
double prevDistance = 400;

unsigned long lastTimeWarningLEDBlinked = millis();
unsigned long warningLEDDelay = 500;
byte warningLEDState = LOW;

void triggerUltrasonicSensor(){
digitalWrite(TRIGGER_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIGGER_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance(){
  double durationMicros = pulseInTimeEnd - pulseInTimeBegin;
  double distance = durationMicros / 58.0;
  if(distance > 400) return prevDistance;

  distance = prevDistance * 0.60 + distance * 0.40;
  prevDistance = distance;
  return distance;
}

void echoPinInterrupt(){
  if(digitalRead(ECHO_PIN) == HIGH){
      pulseInTimeBegin = micros();
  }
  else{
    pulseInTimeEnd = micros();
    newDistanceAvailable = true;
  }
}

void toggleWarningLED(){
  warningLEDState = (warningLEDState == LOW) ? HIGH : LOW;
  digitalWrite(WARNING_LED_PIN, warningLEDState);
}
void setWarningLEDBlinkRateFromDistance(double distance){
warningLEDDelay = distance * 4;
}

void setup() {
Serial.begin(115200);
pinMode(ECHO_PIN, INPUT);
pinMode(WARNING_LED_PIN, OUTPUT);

pinMode(TRIGGER_PIN, OUTPUT);
attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
echoPinInterrupt,
CHANGE);

}

void loop() {
unsigned long timeNow = millis();
  if(timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay){
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
  }

  if(timeNow - lastTimeWarningLEDBlinked > warningLEDDelay){
    lastTimeWarningLEDBlinked += warningLEDDelay;
    toggleWarningLED();
  }

  if(newDistanceAvailable){
double distance = getUltrasonicDistance();
setWarningLEDBlinkRateFromDistance(distance);
Serial.println(distance);
  }

}
