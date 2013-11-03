int verticalPotPin = A0;    // input pin for the vertical position potentiometer
int horizontalPotPin = A1;  // input pin for the horizontal position potentiometer
int ledPin = 13;      // select the pin for the LED
int rowLED[] = {0,1,2,3,4,5,6,7};
int colLED[] = {8,9,10,11,12};
int hVal = 0;  // store the value coming from the  horizontal sensor
int vVal = 0;  // store the value coming from the Vertical potentiometer
void setup() {
  // declare the ledPins as OUTPUTs:
  for(int i = 0; i < 8; i++){
    pinMode(rowLED[i], OUTPUT);
  }
  for(int i = 0; i < 5; i++){
    pinMode(colLED[i], OUTPUT);
  }  
}

void loop() {
  // read the value from the sensor:
  hVal = analogRead(horizontalPotPin);    
  // turn the ledPin on
  digitalWrite(colLED[hVal], HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(hVal);          
  // turn the ledPin off:        
  digitalWrite(colLED[hVal], LOW);   
  // stop the program for for <sensorValue> milliseconds:
  delay(hVal);                  
}
