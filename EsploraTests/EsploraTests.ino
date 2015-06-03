#include <Esplora.h>


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  int red = map(abs(Esplora.readJoystickX()), 0, 512, 0, 255);
  int green = map(abs(Esplora.readJoystickY()), 0, 512, 0, 255);
  int blue = map(Esplora.readSlider(), 0, 1023, 0, 255);
  Esplora.writeRed(red);
  Esplora.writeGreen(green);
  Esplora.writeBlue(blue);
}
