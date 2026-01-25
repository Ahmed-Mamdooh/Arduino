// #include <IRremote.h>

// #define IR_RECEIVE_PIN 5
// // 
// #define IR_BUTTON_0 22

// void setup() {
//   Serial.begin(115200);
//   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
// }

// void loop() {
//   if (IrReceiver.decode()) {
//     Serial.print("HEX: ");
//     Serial.println(IrReceiver.decodedIRData.command);
//     Serial.println("---");
//     IrReceiver.resume();
//   }
// }


// C++ code
//
// C++ code
//
#include<IRremote.h>
#include <LiquidCrystal.h>
#define IR_SENSOR 5
#define BUTTON_0 12
#define BUTTON_1 16
#define BUTTON_2 17
#define BUTTON_3 18
#define ON_OFF 2
#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9
#define LED1 10
#define LED2 11
#define LED3 12

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);



void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  IrReceiver.begin(IR_SENSOR);
  Serial.begin(115200);
  lcd.begin(16,2);
}

void loop()
{

  if(IrReceiver.decode()){
  	int command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    switch(command){
      case BUTTON_0:
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(command);
        lcd.setCursor(0,1);
        lcd.print("ALL LEDs OFF");
        break;

        case BUTTON_1:
        digitalWrite(LED1, !digitalRead(LED1));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(command);
        lcd.setCursor(0,1);
        lcd.print("Toggle LED 1");
        break;

        case BUTTON_2:
        digitalWrite(LED2, !digitalRead(LED2));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(command);
        lcd.setCursor(0,1);
        lcd.print("Toggle LED 2");
        break;

        case BUTTON_3:
        digitalWrite(LED3, !digitalRead(LED3));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(command);
        lcd.setCursor(0,1);
        lcd.print("Toggle LED 3");
        break;

        case ON_OFF:
        lcd.clear();
        break;

        default:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Invalid Signal");
    }
    IrReceiver.resume();
  }
  
}