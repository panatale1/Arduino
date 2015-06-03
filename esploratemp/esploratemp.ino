#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>

char tempPrintout[3];

void setup() {
  EsploraTFT.begin();
  EsploraTFT.background(0,0,0);
  EsploraTFT.stroke(200,20,100);
  EsploraTFT.setTextSize(2);
  EsploraTFT.text("Degress in F :\n",0,0);
  EsploraTFT.setTextSize(5);

}

void loop() {
   String temperature = String(Esplora.readTemperature(DEGREES_F));
   temperature.toCharArray(tempPrintout, 3);
   EsploraTFT.stroke(255,255,255);
   EsploraTFT.text(tempPrintout, 0, 30);
   delay(1000);
   EsploraTFT.stroke(0,0,0);
   EsploraTFT.text(tempPrintout, 0, 30);
}
