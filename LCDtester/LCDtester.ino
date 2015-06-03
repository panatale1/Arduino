#include <LiquidCrystal.h>
//SELECT = 9
//LEFT = 5
//UP = 1
//DOWN = 3
//RIGHT = 0
int topLine = 0;
String array[] = {"Hello, World", "What's up?", "Argentina"};
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int readkey;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("> " + array[topLine]);
  lcd.setCursor(0,1);
  lcd.print(array[topLine + 1]);
}
void loop() {
  readkey=map(analogRead(0),0,1023,0,15);
  Serial.println(readkey);
  if (readkey == 1){
   lcd.clear();
   topLine++;
   lcd.setCursor(0,0);
   lcd.print("> " + array[topLine % 3]);
   lcd.setCursor(0,1);
   lcd.print(array[(topLine + 1) % 3]); 
  }else if (readkey == 3){
    lcd.clear();
    topLine--;
    lcd.setCursor(0,0);
    lcd.print("> " + array[topLine % 3]);
    lcd.setCursor(0,1);
    lcd.print(array[(topLine + 1) % 3]);
  }
  delay(50);
  /*
  if (readkey<50) {
   lcd.clear();
   lcd.print("Button Right");
   }
   else if(readkey<195) {
   lcd.clear();
   lcd.print("Button Up");
   }
   else if(readkey<380) {
   lcd.clear();
   lcd.print("Button Down");
   }
   else if(readkey<790) {
   lcd.clear();
   lcd.print("Button Left");
   }
   */
}

