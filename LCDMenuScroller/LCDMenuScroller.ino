#include <LiquidCrystal.h>
#define SELECT 9
//LEFT = 5
#define UP 1
#define DOWN 3
//RIGHT = 0

#define SIZE 3

int topLine = 0;
String array[] = {
  "Hello, World", "What's up?", "Argentina"};
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int readkey, previous;
void setup() {
  Serial.begin(9600);
  //  pinMode(10,OUTPUT);
  //  analogWrite(10,50);
  lcd.begin(16, 2);
  lcd.print("> " + array[topLine]);
  lcd.setCursor(0,1);
  lcd.print(array[topLine + 1]);
  Serial.println(topLine);
  previous = map(analogRead(0),0,1023,0,15);
}
void loop() {
  readkey=readKeyPad();
  if (readkey == DOWN){
    topLine++;
    lcdPrint(topLine);
  }
  else if (readkey == UP){
    topLine--;
    lcdPrint(topLine);
  }
  else if (readkey == SELECT){
    if (topLine % SIZE < 0){
      Serial.println(array[SIZE + ((topLine) % SIZE)]);
    }
    else{
      Serial.println(array[topLine % SIZE]);
    } 
  }

  delay(150);
}

void lcdPrint(int top){
  lcd.clear();
  lcd.setCursor(0,0);
  if(topLine % 3 < 0){
    lcd.print("> " + array[SIZE + ((top) % SIZE)]);
    //Serial.println(3 + ((topLine) % 3));
    lcd.setCursor(0,1);
    if ((SIZE + (top) % SIZE) == 2){
      lcd.print(array[(top + 1) % SIZE]);
    }
    else{
      lcd.print(array[SIZE + ((top + 1) % SIZE)]);
    }
  }
  else{
    lcd.print("> " + array[top % SIZE]);
    lcd.setCursor(0,1);
    if (topLine >= 0){
      lcd.print(array[(top + 1) % SIZE]);
    }
    else{
      lcd.print(array[SIZE + ((top + 1) % SIZE)]);
    }
  }
}

int readKeyPad(){
  return map(analogRead(0),0,1023,0,15);
}






