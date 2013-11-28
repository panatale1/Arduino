#include <SD.h>
#include <Wire.h>
#include "Arduino.h"
//Ultrasonic Control class
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


int seconds, minutes, hours, _day, _month, _year, _date;
int baseline;
String date;
String timestamp;
Ultrasonic ranger(3);
String dash = "-";
char dataFileName[50];
String slash = "/";
int PIR = 4;
int Capture = 5;
int Flash = 6;
int CS = 10;
File dataFile;
char dirname[50];
char path[11];
void setup(){
  Serial.begin(9600);
  Wire.begin();
  date = getDate();
  Serial.println(date);
  date.toCharArray(dirname,50);
  ranger.DistanceMeasure();
  baseline = ranger.microsecondsToCentimeters();
  Serial.println(baseline);
  if (!SD.begin(10)){
    Serial.println("Initialization failed");
    return;
  }
  Serial.println("SD Card initialized");
  pinMode(Capture,OUTPUT);
  //String tempFileName = String(date + slash + "data.txt");
  date.toCharArray(path,11);
  String(date + slash + "data.txt").toCharArray(dataFileName,50);
  digitalWrite(Capture,HIGH);
  if (!SD.mkdir(path)){
   Serial.println("Directory creation failed"); 
   return;
  }
  dataFile = SD.open(dataFileName,FILE_WRITE);
  dataFile.println(date + "Started at " + getTime() + "\nBaseline = " + baseline + " cm");
  dataFile.close();
  digitalWrite(Capture,LOW);
}
void loop(){

}
String getDate(){
  Wire.beginTransmission(104);
  Wire.write(3);
  Wire.endTransmission();
  Wire.requestFrom(104,4);
  _day = bcdToDec(Wire.read());
  _date = bcdToDec(Wire.read());
  _month = bcdToDec(Wire.read());
  _year = bcdToDec(Wire.read());
  if (_month < 10){
    date = "0";
    date += String(_month);
  }
  else{
    date = String(_month);
  }
  if (_date < 10){
    date += "0" + String(_date);
  }
  else{
    date += String(_date);
  }
  date += "20" + String(_year);
  return date;
}

String getTime(){
  Wire.beginTransmission(104);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(104,3);
  seconds = bcdToDec(Wire.read() & 0x7f);
  minutes = bcdToDec(Wire.read());
  hours = bcdToDec(Wire.read() & 0x3f);
  timestamp = String(hours);
  timestamp += String(minutes);
  timestamp += String(seconds);
  return timestamp;
}
uint8_t decToBcd(int val){
  return (uint8_t) ((val / 10 * 16) + (val % 10)); 
}
int bcdToDec(uint8_t val){
  return (int) ((val / 16 * 10) + (val % 16));
}




