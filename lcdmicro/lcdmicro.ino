#include <TFT.h>
#include <SPI.h>
#include <SD.h>

#define sd_cs 4
#define lcd_cs 10
#define dc 0
#define rst 1

int pot = A3;

TFT TFTscreen = TFT(lcd_cs, dc, rst);

void setup() {
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);
  TFTscreen.stroke(0, 0, 255);
  TFTscreen.background(0, 0, 0);
  TFTscreen.stroke(0, 255, 0);
  TFTscreen.line(0, 10, TFTscreen.width(), 10);
}

void loop() {
  
}
