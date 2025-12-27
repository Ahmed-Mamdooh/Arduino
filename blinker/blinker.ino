// #define   LED_PIN 11
// void setup() {
//   // put your setup code here, to run once:
//     pinMode(13, OUTPUT);

// }


// void loop() {
//   analogWrite(LED_PIN, 20);
//   delay(1500);
//  analogWrite(LED_PIN, 200);
//  delay(500);
//   digitalWrite(LED_PIN, LOW);

//   delay(500);
//   // put your main code here, to run repeatedly:

// }

#define   LED_PIN 11
void setup() {
  // put your setup code here, to run once:
    pinMode(LED_PIN, OUTPUT);

}


void loop() {
for (int i =0; i<=255; i++){
  analogWrite(LED_PIN, i);
  delay(5);
}
for (int i =255; i>=0; i--){
  analogWrite(LED_PIN, i);
  delay(5);
}
  // put your main code here, to run repeatedly:

}

