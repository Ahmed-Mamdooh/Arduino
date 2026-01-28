#define  ECHO_PIN 3
#define TRIGGER_PIN 4
unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;


volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile bool newDistanceAvailable = false;
double prevDistance = 400;

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

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
pinMode(ECHO_PIN, INPUT);
pinMode(TRIGGER_PIN, OUTPUT);
attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                echoPinInterrupt,
                CHANGE);

}

void loop() {
  // put your main code here, to run repeatedly:
unsigned long timeNow = millis();
  if(timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay){
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
  }

  if(newDistanceAvailable){
double distance = getUltrasonicDistance();
Serial.println(distance);
  }

}
