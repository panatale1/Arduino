#include <LiquidCrystal.h>

float conversion = 5000.0/1024.0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int reading;
float millivolts;
float tempC;
float tempF;

void setup() {
    lcd.begin(16, 2);
}

void loop() {
    reading = analogRead(A8);
    millivolts = conversion * reading;
    tempC = (millivolts - 500) / 10;
    tempF = (1.4 * tempC) + 32;
    lcd.setCursor(0, 0);
    lcd.print(String(millivolts) + " mV");
    lcd.setCursor(0, 1);
    lcd.print(String(tempC) + " C, " + String(tempF) + " F");
    delay(500);
}
