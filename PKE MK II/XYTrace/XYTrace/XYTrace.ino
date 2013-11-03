const int xVals[] = {0,1,2,3,4,5,6,7};
const int yVals[] = {8,9,10,11,12,13,14,15};
const int xPot = 5;
const int yPot = 4;
int x, y;
void setup(){
 for (int i = 0; i < 8; i++){
  pinMode(xVals[i],OUTPUT);
  pinMode(yVals[i],OUTPUT);
  digitalWrite(yVals[i],HIGH);
 } 
}

void loop(){
  x = map(analogRead(xPot),0,1023,0,7);
  y = map(analogRead(yPot),0,1023,0,7);
  trace();
}

void trace(){
 digitalWrite(xVals[x],HIGH);
 digitalWrite(yVals[y],LOW);
 delay(3);
 digitalWrite(xVals[x],LOW);
 digitalWrite(yVals[y],HIGH);
 digitalWrite(xVals[y],HIGH);
 digitalWrite(yVals[x],LOW);
 delay(3);
 digitalWrite(xVals[y],LOW);
 digitalWrite(yVals[x],HIGH);
}
