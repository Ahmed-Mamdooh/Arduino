void setup(){
	Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop(){
 int fade_ratio = analogRead(A2) * (255.0/1023.0);
	analogWrite(11, fade_ratio);
}