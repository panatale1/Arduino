const int maximumColumn[] = {0,1,2,3,4,5,6,7};  //array of anode pins
const int maximumHeight[] = {8,9,10,11,12,13,14,15};  //array of cathode pins
//pins for pots
const int heightPot = 5;
const int centerPot = 4;
//values to hold readings from pots to control height and "center" of graph
int center, height;  


void setup(){
 for (int i = 0; i < 8; i++){
  pinMode(maximumColumn[i],OUTPUT);
  pinMode(maximumHeight[i],OUTPUT);
  digitalWrite(maximumHeight[i],HIGH);
 } 
}

void loop(){
 //read the potentiometers
 center = map(analogRead(centerPot),0,1023,0,7);
 height = map(analogRead(heightPot),0,1023,0,7);
 //if the center position reading is 0, make it 1 to have 2 bars at the max height
 if (center == 0){   
  center = 1; 
 }
 drawScreen(); 
}

void drawScreen(){
 //set maxHeight
 int maxHeight = height;
 //iterate through columns left of center position
 for (int i = center - 1; i >= 0; i--){
   //turn on lights in the column up to maxHeight
   for (int j = maxHeight; j >= 0; j--){
    digitalWrite(maximumHeight[j],LOW); 
   }
   digitalWrite(maximumColumn[i],HIGH);
   delay(2);
   //turn lights off again
   for (int k = 0; k < 8; k++){
    digitalWrite(maximumHeight[k],HIGH);
    digitalWrite(maximumColumn[k],LOW); 
   }
   //shrink maxHeight for next column
   maxHeight -= 2;
   //if maxHeight is negative, reset to 0
   if (maxHeight < 0){
     maxHeight = 0;
   }
 }
 //reset maxHeight
 maxHeight = height;
  //iterate through columns to right of center
  for (int i = center; i < 8; i++){
   for (int j = maxHeight; j >= 0; j--){
    digitalWrite(maximumHeight[j],LOW); 
   }
   digitalWrite(maximumColumn[i],HIGH);
   delay(2);
   for (int k = 0; k < 8; k++){
    digitalWrite(maximumHeight[k],HIGH);
    digitalWrite(maximumColumn[k],LOW); 
   }
   maxHeight -= 2;
   if (maxHeight < 0){
     maxHeight = 0;
   }
 } 
}
