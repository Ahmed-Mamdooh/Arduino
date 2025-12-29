#define BUTTON_PIN 2
#define LED 11

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  if(digitalRead(BUTTON_PIN) == HIGH){
  Serial.println("Button is pressed!");
    digitalWrite(LED, HIGH);
  }

  else{
   digitalWrite(LED, LOW); 

  }
  // put your main code here, to run repeatedly:
  delay(250);
}


