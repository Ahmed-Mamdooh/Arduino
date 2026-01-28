#include <LiquidCrystal.h>

#define  ECHO_PIN 3
#define TRIGGER_PIN 4
#define WARNING_LED_PIN 11
#define LOCK_DISTANCE 10.0
#define WARNING_DISTANCE 50.0
#define ERROR_LED_PIN 12
#define BUTTON_PIN 2
#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9
// LiquidCrystal

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// Ultrasonic
unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;


volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile bool newDistanceAvailable = false;
double prevDistance = 400;

// warning LED
unsigned long lastTimeWarningLEDBlinked = millis();
unsigned long warningLEDDelay = 500;
byte warningLEDState = LOW;


// error LED
unsigned long lastTimeErrorLEDBlinked = millis();
unsigned long errorLEDDelay = 300;
byte errorLEDState = LOW;
bool isLocked = false;

// BUTTON
unsigned long lastTimeButtonChanged = millis();
unsigned long  buttonDebounceDelay = 50;
// byte buttonState;
byte buttonState = HIGH;


void setup() {
Serial.begin(115200);
lcd.begin(16,2);
pinMode(ECHO_PIN, INPUT);
pinMode(WARNING_LED_PIN, OUTPUT);
pinMode(ERROR_LED_PIN, OUTPUT);
pinMode(BUTTON_PIN, INPUT);
pinMode(TRIGGER_PIN, OUTPUT);
attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
echoPinInterrupt,
CHANGE);

buttonState = digitalRead(BUTTON_PIN);
lcd.print("Initializing...");
delay(1000);
lcd.clear();
}

void loop() 
{
  unsigned long timeNow = millis();


  if(isLocked){
    if(timeNow - lastTimeErrorLEDBlinked > errorLEDDelay){
      lastTimeErrorLEDBlinked += errorLEDDelay;
      toggleErrorLED();
      toggleWarningLED();
      
    }

    if(timeNow - lastTimeButtonChanged > buttonDebounceDelay){
      byte newButtonState  = digitalRead(BUTTON_PIN);
      if(newButtonState != buttonState){
        lastTimeButtonChanged = timeNow;
          unlock();
      }
    }
  }
  
  else {


    if(timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay){
      lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
      triggerUltrasonicSensor();
    }


    if(timeNow - lastTimeWarningLEDBlinked > warningLEDDelay){
      lastTimeWarningLEDBlinked += warningLEDDelay;
      toggleWarningLED();
    }

    if(newDistanceAvailable){
    double distance = getUltrasonicDistance();
    setWarningLEDBlinkRateFromDistance(distance);
    printDistanceOnLCD(distance);
    if(distance < LOCK_DISTANCE){
      lock();
    printDistanceOnLCD(distance);

      }
    }
  }

}



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

void toggleErrorLED(){
  errorLEDState = (errorLEDState == LOW) ? HIGH : LOW;
  digitalWrite(ERROR_LED_PIN, errorLEDState);
}

void toggleWarningLED(){
  warningLEDState = (warningLEDState == LOW) ? HIGH : LOW;
  digitalWrite(WARNING_LED_PIN, warningLEDState);
}
void setWarningLEDBlinkRateFromDistance(double distance){
  warningLEDDelay = distance * 4;
}


void lock(){
  if(!isLocked){
    isLocked = true;
    warningLEDState= LOW;
    errorLEDState = LOW;
  }
}

void unlock(){
  if(isLocked){
    isLocked = false;
    errorLEDState = LOW;
    digitalWrite(ERROR_LED_PIN, errorLEDState);
  }
}

void printDistanceOnLCD(double distance){
  if (isLocked){
  lcd.setCursor(0,0);
  lcd.print("Obstacle!!      ");
  lcd.setCursor(0,1);
  lcd.print("Press to Unolock");
  
  
  }
  else{
  lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print(" cm     ");
    lcd.setCursor(0, 1);
    
    if(distance > WARNING_DISTANCE){
      lcd.print("No Obstacle.              ");
    }
    else{
      lcd.print("Warning!!           ");
    }

    // lcd.clear();
  }
}