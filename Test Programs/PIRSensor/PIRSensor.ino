/*****************************************************************************/
//	Function: If the sensor detects movement in its detecting range,
//			  the LED is turned on. Otherwise, the LED is turned off.
//  Hardware: Grove - PIR Motion Sensor, Grove - LED
//	Arduino IDE: Arduino-1.0
//	Author:	 Frankie.Chu		
//	Date: 	 Jan 21,2013
//	Version: v1.0
//	by www.seeedstudio.com
//      Modified by: RadioShack Corporation
//      Date: July 18, 2013
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
/*******************************************************************************/
/*macro definitions of PIR motion sensor pin and LED pin*/
#define PIR_MOTION_SENSOR 2//Use pin 2 to receive the signal from the module 
#define LED	5//the LED is connected to D1 of Arduino
#include <SD.h>
#define CS      10//ChipSelect is Pin 10 on SEEEDSTUDIO SD SHIELD
void setup()
{
	pinsInit();
  Serial.begin(9600);
  Serial.println("Initializing card");
  pinMode(CS, OUTPUT);
  if (!SD.begin(CS)){
    Serial.println("Card failed");
    return;
  }
  Serial.println("Initialized");
}

void loop() 
{
  File data = SD.open("data1.txt", FILE_WRITE);
  if(data){
	if(isPeopleDetected()){//if the sensor detects movement, turn on LED.
		turnOnLED();
                Serial.println("HIGH");
                data.println("HIGH");
         }else{//if the sensor does not detect movement, do not turn on LED.
		turnOffLED();
                Serial.println("LOW");
                data.println("LOW");
        }
        data.close();
  }else{
    Serial.println("Could not open file for writing");
  }
  delay(500);
}
void pinsInit()
{
	pinMode(PIR_MOTION_SENSOR, INPUT);
	pinMode(LED,OUTPUT);
}
void turnOnLED()
{
	digitalWrite(LED,HIGH);
}
void turnOffLED()
{
	digitalWrite(LED,LOW);
}
/***************************************************************/
/*Function: Detect whether there is movement in the sensor's detecting range*/
/*Return:-boolean, true is movement is detected.*/
boolean isPeopleDetected()
{
	int sensorValue = digitalRead(PIR_MOTION_SENSOR);
	if(sensorValue == HIGH)//if the sensor value is HIGH?
	{
		return true;//yes,return true
	}
	else
	{
		return false;//no,return false
	}
}
