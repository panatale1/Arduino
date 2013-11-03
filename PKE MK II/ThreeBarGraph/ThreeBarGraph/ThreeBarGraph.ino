const int cols[] = {0,1,2,3,4,5,6,7};
const int rows[] = {8,9,10,11,12,13,14,15};

const int leftPot = 4;
const int rightPot = 5;

int leftHeight, centerHeight, rightHeight;

void setup(){
 for (int i = 0; i < 8; i++){
  pinMode(cols[i],OUTPUT);
  pinMode(rows[i],OUTPUT);
  digitalWrite(rows[i],HIGH);
 } 
}

void loop(){
 leftHeight = map(analogRead(leftPot),0,1023,0,7);
 rightHeight  = map(analogRead(rightPot),0,1023,0,7);
 if (leftHeight == 0){
   centerHeight = abs(1 * rightHeight + 3) % 8;
 }else if (rightHeight == 0){
   centerHeight = abs(leftHeight * 1 + 3) % 8;
 }else{
   centerHeight = abs(leftHeight * rightHeight + 3) % 8;
 }
 drawGraph();
}

void drawGraph(){
 for (int i = 0; i < 3; i++){
   digitalWrite(cols[i],HIGH);
 }
 for (int i = 0; i <= leftHeight; i++){
   digitalWrite(rows[i],LOW);
 }
 delay(2);
 for (int i = 0; i < 8; i++){
   digitalWrite(rows[i],HIGH);
   digitalWrite(cols[i],LOW);
 }
 for (int i = 3; i < 5; i++){
   digitalWrite(cols[i],HIGH);
 }
 for (int i = 0; i <= centerHeight; i++){
   digitalWrite(rows[i],LOW);
 }
  delay(2);
 for (int i = 0; i < 8; i++){
   digitalWrite(rows[i],HIGH);
   digitalWrite(cols[i],LOW);
 }
 for (int i = 5; i < 8; i++){
   digitalWrite(cols[i],HIGH);
 }
 for (int i = 0; i <= rightHeight; i++){
   digitalWrite(rows[i],LOW);
 }
  delay(2);
 for (int i = 0; i < 8; i++){
   digitalWrite(rows[i],HIGH);
   digitalWrite(cols[i],LOW);
 }
}
