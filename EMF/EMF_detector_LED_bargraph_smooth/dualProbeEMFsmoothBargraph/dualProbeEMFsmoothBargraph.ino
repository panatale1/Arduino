// Dual Probe EMF Detector for LED Bargraph v1.0
// 5.2.2012
// original code/project by Aaron ALAI - aaronalai1@gmail.com
// modified for use w/ LED bargraph by Collin Cunningham - collin@makezine.com
// modified for two probes and directional assistane by Peter Natale - panatale1@gmail.com


#define NUMREADINGS 15 // raise this number to increase data smoothing

int senseLimit = 15; // raise this number to decrease sensitivity (up to 1023 max)
int leftProbePin = 5; // analog 5
int leftVal = 0; // reading from leftProbePin
int rightProbePin = 3; // analog 3
int rightVal = 0; // reading from rightProbePin

int leftLED[] = (13,11,9,7,5,3,1};        // pins for left LED graph
int rightLED[] = (12,10,8,6,5,4,2,0};     // pins for right LED graph



// variables for smoothing

int leftReadings[NUMREADINGS];            // the readings from the left analog input
int rightReadings[NUMREADINGS];           // the readings from the right analog input
int leftIndex = 0;                        // the index of the current left reading
int rightIndex = 0;                       // the index of the current right reading
int leftTotal = 0;                        // the left running total
int rightTotal = 0;                       // the right running total
int leftAverage = 0;                      // final average of the left probe reading
int rightAverage = 0;                     // final average of the right probe reading


void setup() {
  for(int i = 0; i < 7; i++){
    pinMode(leftLED[i], OUTPUT);          // Set each pin connector for output
    pinMode(rightLED[i], OUTPUT);
  }

  Serial.begin(9600);  // initiate serial connection for debugging/etc

  for (int i = 0; i < NUMREADINGS; i++){
    leftReadings[i] = 0;                      // initialize all the leftReadings to 0
    rightReadings[i] = 0;                     // initialize all the rightReadings to 0
   }
}

void loop() {

  leftVal = analogRead(leftProbePin);  // take a reading from the left probe
  rightVal = analogRead(rightProbePin); // take a reading from the right probe

  if(leftVal >= 1){                // if the reading isn't zero, proceed

    leftVal = constrain(leftVal, 1, senseLimit);  // turn any reading higher than the senseLimit value into the senseLimit value
    leftVal = map(leftVal, 1, senseLimit, 1, 1023);  // remap the constrained value within a 1 to 1023 range

    leftTotal -= leftReadings[leftIndex];                // subtract the last reading
    leftReadings[leftIndex] = leftVal;                   // read from the sensor
    leftTotal += leftReadings[leftIndex];               // add the reading to the total
    leftIndex++;                                    // advance to the next index

    if (leftIndex >= NUMREADINGS)               // if we're at the end of the array...
      leftIndex = 0;                            // ...wrap around to the beginning

    leftAverage = leftTotal / NUMREADINGS;          // calculate the average
    leftAverage = map(leftAverage,0,1023,0,6);      // remap to between 0 and 6

    for (int i = 0; i < 7; i++){                     // if remapped value greater than bargraph index
      if(leftAverage > i)                            // light up proper LEDs
        digitalWrite(leftLED[i], HIGH);
      else
        digitalWrite(leftLED[i], LOW);  
    }



    Serial.println(leftVal); // use output to aid in calibrating
  }
  if(rightVal >= 1){                // if the reading isn't zero, proceed

    rightVal = constrain(rightVal, 1, senseLimit);  // turn any reading higher than the senseLimit value into the senseLimit value
    rightVal = map(rightVal, 1, senseLimit, 1, 1023);  // remap the constrained value within a 1 to 1023 range

    rightTotal -= rightReadings[rightIndex];                // subtract the last reading
    rightReadings[rightIndex] = rightVal;                   // read from the sensor
    rightTotal += rightReadings[rightIndex];               // add the reading to the total
    rightIndex++;                                    // advance to the next index

    if (rightIndex >= NUMREADINGS)               // if we're at the end of the array...
      rightIndex = 0;                            // ...wrap around to the beginning

    rightAverage = rightTotal / NUMREADINGS;          // calculate the average
    rightAverage = map(rightAverage,0,1023,0,6);
    for(int i = 0; i < 7; i++){
      if(rightAverage > i)
        digitalWrite(rightLED[i], HIGH);
      else
        digitalWrite(rightLED[i], LOW);
    }


    Serial.println(rightVal); // use output to aid in calibrating
  }
}
