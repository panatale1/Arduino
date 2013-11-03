// EMF Detector for LED Bargraph v1.1
// 5.12.2009
// original code/project by Aaron ALAI - aaronalai1@gmail.com
// modified for use w/ LED bargraph by Collin Cunningham - collin@makezine.com
// modified for more efficient code by Peter Natale - panatale1@gmail.com


#define NUMREADINGS 15 // raise this number to increase data smoothing

int senseLimit = 15; // raise this number to decrease sensitivity (up to 1023 max)
int probePin = 5; // analog 5
int val = 0; // reading from probePin


int LED[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2}; //connections to LED bargraph anodes with resistors in series

// variables for smoothing

int readings[NUMREADINGS];                // the readings from the analog input
int index = 0;                            // the index of the current reading
int total = 0;                            // the running total
int average = 0;                          // final average of the probe reading


void setup() {
  for (int i = 0; i < 10; i++){
    pinMode(LED[i], OUTPUT);
  }

  Serial.begin(9600);  // initiate serial connection for debugging/etc

  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;                      // initialize all the readings to 0
}

void loop() {

  val = analogRead(probePin);  // take a reading from the probe

  if(val >= 1){                // if the reading isn't zero, proceed

    val = constrain(val, 1, senseLimit);  // turn any reading higher than the senseLimit value into the senseLimit value
    val = map(val, 1, senseLimit, 1, 1023);  // remap the constrained value within a 1 to 1023 range

    total -= readings[index];               // subtract the last reading
    readings[index] = val; // read from the sensor
    total += readings[index];               // add the reading to the total
    index = (index + 1);                    // advance to the next index

    if (index >= NUMREADINGS)               // if we're at the end of the array...
      index = 0;                            // ...wrap around to the beginning

    average = total / NUMREADINGS;          // calculate the average
    
    average = map(average, 1, 1023, 0, 9);  // remap average to between 0 and 9
    
    for (int i = 0; i < 10; i++){           //light corresponded LEDs
      if(average >= LED[i])
        digitalWrite(LED[i], HIGH);
      else
        digitalWrite(LED[i], LOW);
    }

    Serial.println(val); // use output to aid in calibrating
  }
}
