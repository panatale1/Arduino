#include <SD.h>

/**
FOR THE SEEEDSTUDIO SD SHIELD:
 MOSI - PIN 11
 MISO - PIN 12
 CLK - PIN 13
 CS - PIN 10

PIR Sensor attached to Pins 0-2
 Pin 0 - signal
 Pin 1 - 5V
 Pin 2 - Ground
 
LED attached to Pin 8
LED ground at 9
*/

int IRGnd = 2;
int IRSig = 0;
int IRVlt = 1;
int LED = 8;
int LEDGnd = 9;
int CS = 10;
void setup(){
  pinMode(IRGnd, OUTPUT);
  digitalWrite(IRGnd, LOW);
  pinMode(IRVlt, OUTPUT);
  digitalWrite(IRVlt, HIGH);
  pinMode(IRSig, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(LEDGnd, OUTPUT);
  digitalWrite(LEDGnd, LOW);
  Serial.begin(9600);
  Serial.print("Initializing card");
  pinMode(10, OUTPUT);
  if (!SD.begin(CS)){
    Serial.println("Card failed");
    return;
  }
  Serial.println("Initialized");
}

void loop(){
  File data = SD.open("data.txt",FILE_WRITE);
  if(data){
   if(digitalRead(IRSig)){
    Serial.println("HIGH");
    data.println("HIGH");
    digitalWrite(LED,HIGH);
   }else{
    Serial.println("LOW");
    data.println("LOW");
    digitalWrite(LED,LOW);
   } 
   data.close();
  }else{
   Serial.println("Error opening data.txt");
  }
}
