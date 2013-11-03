// EMF Detector for LED Bargraph v1.0
// 5.12.2009
// original code/project by Aaron ALAI - aaronalai1@gmail.com
// modified for use w/ LED bargraph by Collin Cunningham - collin@makezine.com


#define NUMREADINGS 30 // raise this number to increase data smoothing

int senseLimit = 15; // raise this number to decrease sensitivity (up to 1023 max)
int probePin = 5; // analog 5
int val = 0; // reading from probePin

int LED[] = {11,10,9,6};

// variables for smoothing

int readings[NUMREADINGS];                // the readings from the analog input
int index = 0;                            // the index of the current reading
int total = 0;                            // the running total
int average = 0;                          // final average of the probe reading


void setup() {
  for(int i = 0; i < 4; i++){
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
    
    if(average >= 768){
      analogWrite(LED[0], 255);
      analogWrite(LED[1], 255);
      analogWrite(LED[2], 255);
      analogWrite(LED[3], average - 768);
    }else if(average >= 512){
      analogWrite(LED[3], 0);
      analogWrite(LED[0], 255);
      analogWrite(LED[1], 255);
      analogWrite(LED[2], average - 512);
    }else if(average >= 256){
      analogWrite(LED[2], 0);
      analogWrite(LED[3], 0);
      analogWrite(LED[0], 255);
      analogWrite(LED[1], average - 256);
    }else{
      analogWrite(LED[1], 0);
      analogWrite(LED[2], 0);
      analogWrite(LED[3], 0);
      analogWrite(LED[0], average);
    }


    Serial.println(val); // use output to aid in calibrating
  }
}
