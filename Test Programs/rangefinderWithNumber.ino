#include "Arduino.h"
class Ultrasonic
{
	public:
		Ultrasonic(int pin);
        void DistanceMeasure(void);
		long microsecondsToCentimeters(void);
		long microsecondsToInches(void);
	private:
		int _pin;//pin number of Arduino that is connected with SIG pin of Ultrasonic Ranger.
        long duration;// the Pulse time received;
};
Ultrasonic::Ultrasonic(int pin)
{
	_pin = pin;
}
/*Begin the detection and get the pulse back signal*/
void Ultrasonic::DistanceMeasure(void)
{
    pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(_pin,LOW);
	pinMode(_pin,INPUT);
	duration = pulseIn(_pin,HIGH);
}
/*The measured distance from the range 0 to 400 Centimeters*/
long Ultrasonic::microsecondsToCentimeters(void)
{
	return duration/29/2;	
}
/*The measured distance from the range 0 to 157 Inches*/
long Ultrasonic::microsecondsToInches(void)
{
	return duration/74/2;	
}

int topLeftVert = 1;
int middleHor = 2;
int botLeftVert = 3;
int botHor = 4;
int botRightVert = 5;
int dp = 6;
int topRightVert = 7;
int topHor = 8;

Ultrasonic ultrasonic(13);
long range;
void setup(){
 pinMode(topLeftVert,OUTPUT);
 pinMode(middleHor,OUTPUT);
 pinMode(botLeftVert,OUTPUT);
 pinMode(botHor,OUTPUT);
 pinMode(botRightVert,OUTPUT);
 pinMode(dp,OUTPUT);
 pinMode(topRightVert,OUTPUT);
 pinMode(topHor,OUTPUT);
 disp0();
 delay(500);
 disp1();
  delay(500);
 disp2();
  delay(500);
 disp3();
  delay(500);
 disp4();
  delay(500);
 disp5();
  delay(500);
 disp6();
  delay(500);
 disp7();
  delay(500);
 disp8();
  delay(500);
 disp9(); 
 delay(500);
}

void loop(){
  ultrasonic.DistanceMeasure();
  range = ultrasonic.microsecondsToCentimeters() / 100;
  range = map(range,0,400,0,9);
  if (range < 1){
    disp0();
  }else if(range < 2){
    disp1();
  }else if(range < 3){
    disp2();
  }else if (range < 4){
    disp3();
  }else if (range < 5){
    disp4();
  }else if(range < 6){
    disp5();
  }else if(range < 7){
    disp6();
  }else if(range < 8){
    disp7();
  }else if (range < 9){
    disp8();
  }else{
    disp9();
  }
  delay(500);
}
void writeLow(){
 digitalWrite(topLeftVert,LOW);
 digitalWrite(middleHor,LOW);
 digitalWrite(botLeftVert,LOW);
 digitalWrite(botHor,LOW);
 digitalWrite(botRightVert,LOW);
 digitalWrite(dp,LOW);
 digitalWrite(topRightVert,LOW);
 digitalWrite(topHor,LOW);
}
void disp0(){
  writeLow();
  digitalWrite(topLeftVert,HIGH);
  digitalWrite(botLeftVert,HIGH);
  digitalWrite(botHor,HIGH);
  digitalWrite(botRightVert,HIGH);
  digitalWrite(topRightVert,HIGH);
  digitalWrite(topHor,HIGH);
}
void disp1(){
  writeLow();
  digitalWrite(topRightVert,HIGH);
  digitalWrite(botRightVert,HIGH);
}
void disp2(){
  writeLow();
  digitalWrite(topHor,HIGH);
  digitalWrite(topRightVert,HIGH);
  digitalWrite(middleHor,HIGH);
  digitalWrite(botLeftVert,HIGH);
  digitalWrite(botHor,HIGH);
}
void disp3(){
  writeLow();
  digitalWrite(topHor,HIGH);
  digitalWrite(middleHor,HIGH);
  digitalWrite(botHor,HIGH);
  digitalWrite(topRightVert,HIGH);
  digitalWrite(botRightVert,HIGH);
}
void disp4(){
  writeLow();
  digitalWrite(middleHor,HIGH);
  digitalWrite(topLeftVert,HIGH);
  digitalWrite(topRightVert,HIGH);
  digitalWrite(botRightVert,HIGH);
}
void disp5(){
  writeLow();
  digitalWrite(topHor,HIGH);
  digitalWrite(middleHor,HIGH);
  digitalWrite(botHor,HIGH);
  digitalWrite(topLeftVert,HIGH);
  digitalWrite(botRightVert,HIGH);
}
void disp6(){
  writeLow();
  digitalWrite(topHor,HIGH);
  digitalWrite(middleHor,HIGH);
  digitalWrite(botHor,HIGH);
  digitalWrite(topLeftVert,HIGH);
  digitalWrite(botLeftVert,HIGH);
  digitalWrite(botRightVert,HIGH);
}
void disp7(){
  writeLow();
  digitalWrite(topHor,HIGH);
  digitalWrite(topRightVert,HIGH);
  digitalWrite(botRightVert,HIGH);
}
void disp8(){
  writeLow();
  digitalWrite(topHor,HIGH);
  digitalWrite(middleHor,HIGH);
  digitalWrite(botHor,HIGH);
  digitalWrite(topLeftVert,HIGH);
  digitalWrite(botLeftVert,HIGH);
  digitalWrite(topRightVert,HIGH);
  digitalWrite(botRightVert,HIGH);
}
void disp9(){
  writeLow();
  digitalWrite(topHor,HIGH);
  digitalWrite(middleHor,HIGH);
  digitalWrite(topLeftVert,HIGH);
  digitalWrite(topRightVert,HIGH);
  digitalWrite(botRightVert,HIGH);
}