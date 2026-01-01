#define POTENTIO A2
#define RED 11
#define YELLOW 10
#define GREEN 9
void setup(){
	Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop(){
  digitalWrite(RED, HIGH);
  delay(3000);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  delay(3000);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(1000);
  digitalWrite(YELLOW, LOW);
  // It can be more readable by setting all the three in every delay, but I think that this code is so simple so no need for that.
 
}