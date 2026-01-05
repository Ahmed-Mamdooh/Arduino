#define LED1 11
#define LED2 10
#define LED3 9
#define POTMET A2

#define BUTTON 2
unsigned long blinkDelay = 500;
unsigned long lastTimeBlink = 0;

void setup(){
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);

  pinMode(LED2, OUTPUT);
  
  pinMode(POTMET, INPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.setTimeout(10);
}

void loop(){
  unsigned long timeNow = millis();
  if(Serial.available() > 0){
    int data = Serial.parseInt();
    if (data > 0 && data <= 4000) blinkDelay = data;
  }
  
  if(timeNow - lastTimeBlink >= blinkDelay){
      digitalWrite(LED1, !digitalRead(LED1));
    lastTimeBlink = timeNow;
  }

  
  
int fade_ratio = analogRead(POTMET) / 4;
  analogWrite(LED2, fade_ratio);

  

if(digitalRead(BUTTON) == HIGH) digitalWrite(LED3, HIGH);
else digitalWrite(LED3, LOW);

}
