#include <TFT.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

#define sd_cs     4
#define lcd_cs   10
#define dc        0
#define rst       1
#define radius    8

int ycenters[] = {110, 94, 78, 62, 46, 30, 14};
int xcenters[] = {131, 115, 99, 83, 67, 51, 35};

int xPos = 80;
int yPos = 64;

int xDir = 1;
int yDir = 1;

int xPrev = xPos;
int yPrev = yPos;

int pot = A3;

Servo wings;

TFT TFTscreen = TFT(lcd_cs, dc, rst);

void setup() {
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.fill(0, 255, 0);
  for (int i=0; i < 7; i += 1){
    TFTscreen.circle(xcenters[i], ycenters[i], radius);
  }
  wings.attach(12);
}

void loop() {
  for (int i = 0; i < 7; i += 1){
    wings.write(map(analogRead(pot), 0, 1023, 0, 90));
    TFTscreen.fill(0, 0, 0);
    TFTscreen.circle(xcenters[i], ycenters[i], radius);
    delay(map(analogRead(pot), 0, 1023, 100, 500));
    wings.write(map(analogRead(pot), 0, 1023, 0, 90));
    TFTscreen.fill(0, 255, 0);
    TFTscreen.circle(xcenters[i], ycenters[i], radius);
    //delay(map(analogRead(pot), 0, 1023, 50, 250));
    if (i==6){
     delay(map(analogRead(pot), 0, 1023, 100, 500)); 
    }
    else {
      delay(25);
    }
  }
}
