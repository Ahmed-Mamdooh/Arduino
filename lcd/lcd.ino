
//#include <LiquidCrystal.h>
//#define LCD_RS A5
//#define LCD_E A4
//#define LCD_D4 6
//#define LCD_D5 7
//#define LCD_D6 8
//#define LCD_D7 9

//LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//void setup() {
  // put your setup code here, to run once:
//  lcd.begin(16,2);
//  lcd.print("Hello World");

//}

//void loop() {
  // put your main code here, to run repeatedly:

//}


// #include <LiquidCrystal.h>
// #define LCD_RS A5
// #define LCD_E A4
// #define LCD_D4 6
// #define LCD_D5 7
// #define LCD_D6 8
// #define LCD_D7 9

// LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
// int counter = 0;
// void setup() {
//   // put your setup code here, to run once:
// lcd.begin(16,2);
// lcd.print("Hello");
// }

// void loop() {
//   lcd.setCursor(6, 0);
//   lcd.print(counter);
//   counter++;
//   delay(500);
//   // put your main code here, to run repeatedly:

//}



//#include <LiquidCrystal.h>
//#define LCD_RS A5
//#define LCD_E A4
//#define LCD_D4 6
//#define LCD_D5 7
//#define LCD_D6 8
//#define LCD_D7 9

//LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//void setup() {
  // put your setup code here, to run once:
//  lcd.begin(16,2);
//  lcd.print("Hello World");

//}

//void loop() {
  // put your main code here, to run repeatedly:

//}


// #include <LiquidCrystal.h>
// #define LCD_RS A5
// #define LCD_E A4
// #define LCD_D4 6
// #define LCD_D5 7
// #define LCD_D6 8
// #define LCD_D7 9

// LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
// int counter = 0;
// void setup() {
//   // put your setup code here, to run once:
// lcd.begin(16,2);
// lcd.print("Hello");
// }

// void loop() {
//   lcd.setCursor(6, 0);
//   lcd.print(counter);
//   counter++;
//   delay(500);
//   // put your main code here, to run repeatedly:

//}


// #include <LiquidCrystal.h>
// #define LCD_RS A5
// #define LCD_E A4
// #define LCD_D4 6
// #define LCD_D5 7
// #define LCD_D6 8
// #define LCD_D7 9


// LiquidCrystal lcd(LCD_RS,LCD_E,  LCD_D4, LCD_D5, LCD_D6,LCD_D7);
// int textPlace = 0;

// void setup(){
// Serial.begin(115200);
// lcd.begin(16, 2);
// }

// void loop(){
// if (Serial.available() > 0){
//   String data =  Serial.readString();
//   if (data.length() > 16) {
//     Serial.print("This text is more than allowed (16), it is ");
//     Serial.print(data.length());
//     Serial.print(" characters");
//     return;
//   }

// lcd.setCursor(0, textPlace);
// lcd.print("              ");
// lcd.setCursor(0, textPlace);
// lcd.print(data);
// textPlace = textPlace == 0 ? 1 : 0;

// }
// }

#include <LiquidCrystal.h>

#define TRIG 4
#define ECHO 3
#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

int cursorLine = 0;


unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;

volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile bool newDistanceAvailable = false;

double previousDistance = 400.0;


void tiggerUltrasonicSensor(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
}

double getUltrasonicDistance(){
  double durationMicros = pulseInTimeEnd - pulseInTimeBegin;
  double distance = durationMicros / 58.0;
  if(distance > 400.0) distance = previousDistance;

  distance = previousDistance * 0.7 + distance * 0.3;

  previousDistance  = distance;
  return distance;
}


void echoPinInterrupt(){
  if(digitalRead(ECHO) == HIGH){
    pulseInTimeBegin = micros();
    }
  else{
    pulseInTimeEnd = micros();
    newDistanceAvailable = true;
  }
}

void printDistanceOnLCD(double distance){
  lcd.setCursor(0,1);
  lcd.print("Distance:  ");
  lcd.print(distance);
}

void setup(){
  Serial.begin(115200);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO), echoPinInterrupt, CHANGE);
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("Rate: ");
lcd.print(ultrasonicTriggerDelay);
lcd.print(" ms.");

}


void loop(){
  unsigned long timeNow = millis();
  if(timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay){
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    tiggerUltrasonicSensor();
  }
  if(newDistanceAvailable){
    newDistanceAvailable = false;
    double distance = getUltrasonicDistance();
    printDistanceOnLCD(distance);
  }
}