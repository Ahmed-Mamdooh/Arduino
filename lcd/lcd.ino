
#include <LiquidCrystal.h>
#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 7
#define LCD_D6 8
#define LCD_D7 9

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7)

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("Hello World");

}

void loop() {
  // put your main code here, to run repeatedly:

}
