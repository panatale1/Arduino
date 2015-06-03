//#include <SPI.h>
#include <LiquidCrystal.h>
#include <SD.h>
int lineNo = 1;
File myFile;
LiquidCrystal lcd(8,9,4,5,6,7);
void setup(){
  pinMode(53,OUTPUT);
  lcd.begin(16,2);
  if (!SD.begin(4)){
    lcd.print("Card Failed");
  } 
  myFile = SD.open("test.txt",FILE_WRITE);

  if (myFile){
    lcd.clear();
    lcd.print("Writing to");
    lcd.setCursor(0,1);
    lcd.print("test.txt");
    delay(500);
    myFile.println("testing 1,2,3");
    lcd.clear();
    lcd.print("done");
    delay(500);
    myFile.close();
  }
  else{
    lcd.clear();
    lcd.print("error opening");
    lcd.setCursor(0,1);
    lcd.print("test.txt");

  }

  myFile = SD.open("test.txt");
  if (myFile){
    lcd.clear();
    lcd.print("test.txt:");

    while(myFile.available()){
      char input = myFile.read();
      lcd.setCursor(0,1);
      lcd.print(lineNo);
      lcd.write(' ');
      while (input != '\n'){
        lcd.write(input);
        input = myFile.read();
      }
      delay(500);
      lineNo++;
    }
    myFile.close();
  }
  else{
    lcd.clear();
    lcd.print("error opening");
    lcd.setCursor(0,1);
    lcd.print("test.txt");
  }
}
void loop(){

}



