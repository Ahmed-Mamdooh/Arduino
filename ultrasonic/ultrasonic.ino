
#define ECHO 3
#define TRIG 4

unsigned long lastTimeUlTrig = millis();
unsigned long ulDelay = 100;

void triggerUlSensor(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
}

double getUlDistance(){
  
  // unsigned long 
  double durationMicros = pulseIn(ECHO, HIGH);
  double distance = durationMicros / 58.0;
  return distance;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);


}

void loop() {
  unsigned long timeNow = millis();
  if(timeNow - lastTimeUlTrig > ulDelay){
    lastTimeUlTrig += ulDelay;
     triggerUlSensor();
     Serial.println(getUlDistance());
  }

 
  // put your main code here, to run repeatedly:

}
