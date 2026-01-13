// Lite Code...
// # define BTN 2
// # define LED 12

// byte LEDState = LOW;
// volatile bool buttonReleased = false;

// void buttonRealseInterrupt(){
// buttonReleased = true;
// }

// void toggle(){
//   if(LEDState == LOW){
//     LEDState = HIGH;
//   }
//   else{
//      LEDState = LOW;
//   }

//   digitalWrite(LED, LEDState);
// }

// void setup() {
//  pinMode(BTN, INPUT);
//  pinMode(LED, OUTPUT);

//  attachInterrupt(digitalPinToInterrupt(BTN), buttonRealseInterrupt, FALLING);
// }

// void loop() {
//   if(buttonReleased){
//     buttonReleased = false;
//     toggle();
//   }

// }


// !!!!!!! - !!!!!!! - !!!!!!! - Code with debounce ==>

// # define BTN 2
// # define LED 12

// byte LEDState = LOW;
// volatile bool buttonReleased = false;
// int debounceDelay = 50;
// unsigned long lastReleasedTime = millis();


// void buttonRealseInterrupt(){
//   unsigned long timeNow = millis();

// if(timeNow - lastReleasedTime > debounceDelay){
//   buttonReleased = true;
//   lastReleasedTime = timeNow;
// }
// }

// void toggle(){
//   if(LEDState == LOW){
//     LEDState = HIGH;
//   }
//   else{
//      LEDState = LOW;
//   }

//   digitalWrite(LED, LEDState);
// }

// void setup() {
//  pinMode(BTN, INPUT);
//  pinMode(LED, OUTPUT);

//  attachInterrupt(digitalPinToInterrupt(BTN), buttonRealseInterrupt, FALLING);
// }

// void loop() {
//   if(buttonReleased){
//     buttonReleased = false;
//     toggle();
//   }

// }


// !!!!!!! - !!!!!!! - !!!!!!! - Activity
#define BTN 2

volatile int interrputionCounter = 0;
volatile bool buttonReleased = false;
unsigned long lastRelease = millis();
int debounceDelay = 100; 

void buttonReleasedInterrupt(){
  unsigned long timeNow = millis();
   
  if(timeNow - lastRelease > debounceDelay){
     buttonReleased = true;
    interrputionCounter += 1;
  }
  
}

void setup(){
pinMode(BTN, INPUT);
attachInterrupt(digitalPinToInterrupt(BTN), buttonReleasedInterrupt, RISING);
Serial.begin(115200);
}

void loop(){
  if(buttonReleased){
     buttonReleased = false;
     Serial.println(interrputionCounter);
  };
}
