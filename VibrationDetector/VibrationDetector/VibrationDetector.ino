#define NUMREADINGS 15 // raise this number to increase data smoothing

int senseLimit = 15; // raise this number to decrease sensitivity (up to 1023 max)
int readings[NUMREADINGS];            // the readings from the left analog input
int total = 0;
int avg = 0;
const int LEDs[] = {0,1,2,3,4,5,6,7,8,9};
const int vibSense = 0;
int index = 0;

int val;

void setup(){
  for (int i = 0; i < 10; i++){
    pinMode(LEDs[i],OUTPUT);
    digitalWrite(LEDs[i],LOW);
  }
  for (int i = 0; i < NUMREADINGS; i++){
    readings[i] = 0;
  }
}
void loop(){
  val = analogRead(vibSense);
  if (val >= 1){
  val = map(constrain(val,1,senseLimit),1,senseLimit,0,1023);
  total -= readings[index];
  readings[index] = val;
  total += readings[index];
  index++;
  avg = map(total / NUMREADINGS,0,1023,0,9);
  
  for (int i = 0; i < 10; i++){
    if (avg >= i){
      digitalWrite(LEDs[i],HIGH);
    }else{
      digitalWrite(LEDs[i],LOW);
   } 
 }
  }
  
}
