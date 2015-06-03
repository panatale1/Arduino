#include <Wire.h>
//Set to 10:21 AM, Saturday, November 16, 2013 EST
//Upload takes approximately 10 seconds

int seconds = 00;
int minutes = 21;
int hours = 10;
int _day = 6;
int date = 16;
int _month = 11;
int _year = 13;
String colon = ":";
String dash = "-";
String _hour;
String _minute;
String time;
String theyear;
String themonth;
String thedate;

void setup(){
  Wire.begin(); 
  //set_date();
  set_time();
  Serial.begin(9600);
}
void loop(){
  get_time();
  get_date();
  display_date();
  display_time();
  delay(1000); 
}
void set_date(){
  Wire.beginTransmission(104);
  Wire.write(3);
  Wire.write(decToBcd(_day));
  Wire.write(decToBcd(date));
  Wire.write(decToBcd(_month));
  Wire.write(decToBcd(_year));
  Wire.endTransmission();
}
void get_date(){
  Wire.beginTransmission(104);
  Wire.write(3);
  Wire.endTransmission();
  Wire.requestFrom(104,4);
  _day = bcdToDec(Wire.read());
  date = bcdToDec(Wire.read());
  _month = bcdToDec(Wire.read());
  _year = bcdToDec(Wire.read());
}
void set_time(){
  Wire.beginTransmission(104);
  Wire.write(0);
  Wire.write(decToBcd(seconds));
  Wire.write(decToBcd(minutes));
  Wire.write(decToBcd(hours));
  Wire.endTransmission();
}
void get_time(){
  Wire.beginTransmission(104);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(104,3);
  seconds = bcdToDec(Wire.read() & 0x7f);
  minutes = bcdToDec(Wire.read());
  hours = bcdToDec(Wire.read() & 0x3f);
}
void display_time(){
  if (hours < 10){
    String hour1 = "0";
    _hour = hour1 + String(hours);
  }
  else{
    _hour = String(hours);
  }

  if (minutes < 10){
    _minute = _hour + colon + "0" + String(minutes);
  }
  else{
    _minute = _hour + colon + String(minutes);
  }

  if (seconds < 10){
    time = _minute + colon + "0" + String(seconds);
  }
  else{
    time = _minute + colon + String(seconds);
  }
  Serial.println(time);
}
void display_date(){
  String theyear1 = "20";
  String theyear  = theyear1 + String(_year);
  String themonth = theyear + dash + String(_month);
  if (_day < 10){
    thedate = themonth + dash + "0" + String(_day);
  }
  else{
    thedate = themonth + dash + String(_day);
  }
  Serial.print(thedate + "\t");
}

uint8_t decToBcd(int val){
  return (uint8_t) ((val / 10 * 16) + (val % 10)); 
}
int bcdToDec(uint8_t val){
  return (int) ((val / 16 * 10) + (val % 16));
}

