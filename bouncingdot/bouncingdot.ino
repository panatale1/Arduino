#include <TFT.h>
#include <SPI.h>
#include <SD.h>

#define sd_cs 4
#define lcd_cs 10
#define dc 0
#define rst 1

int xPos = 80;
int yPos = 64;

int xDir = 1;
int yDir = 1;

int xPrev = xPos;
int yPrev = yPos;

int pot = A3;

TFT TFTscreen = TFT(lcd_cs, dc, rst);

void setup() {
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
}

void loop() {
  xPos = xPos + xDir;
  yPos = yPos + yDir;
  
  if (xPos != xPrev || yPos != yPrev){
    TFTscreen.stroke(0,0,0);
    TFTscreen.point(xPrev, yPrev);
  }
  TFTscreen.stroke(0,255,0);
  TFTscreen.point(xPos, yPos);
  
  if (xPos >= 160 || xPos <= 0) {
   xDir = xDir * -1;
  }
  if (yPos >= 128 || yPos <= 0){
   yDir = yDir * -1; 
  }
  xPrev = xPos;
  yPrev = yPos;
  delay(map(analogRead(pot), 0, 1023, 5, 60));
}
