/*
Servo attached to pin 9.  GET SECOND SERVO TO ATTACH TO 8
Green LED from Pin 13 to GND
Red LED from Pin 12 to GND
Button between Pin 2 and 5V
10 kOhm resistor between Pin 2 and GND
*/
#include <Servo.h>

Servo servo1, servo2;
int inPin = 2;
int redPin = 12;
int greenPin = 13;
int reading;
int state = HIGH;
int previous = LOW;
long time = 0;
long debounce = 200;
int redState = HIGH;
int greenState = LOW;
void setup(){
  servo1.attach(9);
  servo2.attach(8);

  pinMode(inPin, INPUT);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
}

void loop(){
  reading = digitalRead(inPin);
  if (reading && !previous &&millis() - time > debounce){
    if (redState){
      redState = LOW;
      greenState = HIGH;
      servo1.write(0);
      servo2.write(179);
    }else{
      redState = HIGH;
      greenState = LOW;
      servo1.write(90);
      servo2.write(90);
    }
    time=millis();
  }
  delay(15);
  digitalWrite(redPin, redState);
  digitalWrite(greenPin, greenState);
}
