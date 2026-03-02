#include <Servo.h>
Servo myServo;
int pos = 0;
void setup() {
  myServo.attach(9);
  // put your setup code here, to run once:

}

void loop() {
  for(pos = 0; pos<=180; pos++){
    myServo.write(pos);
    delay(15);
  }

    for(pos = 180; pos>=0; pos--){
    myServo.write(pos);
    delay(15);
  }
  // put your main code here, to run repeatedly:

}
