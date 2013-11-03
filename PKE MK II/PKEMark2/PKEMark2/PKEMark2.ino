const int anodes[] = {23,25,27,29,31,33,35,37};
const int mode1 = 2;
const int mode2 = 3;
const int redSwitch = 14;
const int blueSwitch = 15;
const int greenSwitch = 16;
const int purpleSwitch = 17;
const int yellowSwitch = 18;
const int antennaeAnodes[] = {44,45};
const int reds[] = {41,43};
const int blues[] = {47,49};
const int greens[] = {51,53};
const int greenMatrix[] = {24,28,32,36,40,39,48,52};
const int redMatrix[] = {22,26,30,34,38,42,46,50};
const int threeBars[] = {24,28,32,36,40,42,46,50};
const int dimmerPot = 7;
const int horizontalPot = 6;
const int verticalPot = 5;
const int DELAY = 2;
int center, height, brightness;

void setup(){
 for (int i = 22; i < 53; i += 2){
  pinMode(i,OUTPUT);
  digitalWrite(i,HIGH);
 }
 for (int i = 0; i < 8; i++){
   pinMode(anodes[i],OUTPUT);
 }
 pinMode(mode1,INPUT);
 pinMode(mode2,INPUT);
 pinMode(redSwitch,INPUT);
 pinMode(blueSwitch,INPUT);
 pinMode(greenSwitch,INPUT);
 pinMode(purpleSwitch,INPUT);
 pinMode(yellowSwitch,INPUT);
 for (int i = 0; i < 2; i++){
  pinMode(antennaeAnodes[i],OUTPUT);
  pinMode(reds[i],OUTPUT);
  digitalWrite(reds[i],HIGH);
  pinMode(blues[i],OUTPUT);
  digitalWrite(blues[i],HIGH);
  pinMode(greens[i],OUTPUT);
  digitalWrite(greens[i],HIGH);
 }
}

void loop(){
  brightness = map(analogRead(dimmerPot),0,1023,0,255);
  center = map(analogRead(horizontalPot),0,1023,0,7);
  height = map(analogRead(verticalPot),0,1023,0,7);
  colors();
  if (digitalRead(mode1) == HIGH){
    graph();
  }else if (digitalRead(mode2) == HIGH){
    threeBar();
  }else{
    trace();
  }
}

void colors(){
  if (digitalRead(redSwitch) == HIGH){
    for(int i = 0; i < 2; i++){
     digitalWrite(reds[i],LOW);
     digitalWrite(blues[i],HIGH);
     digitalWrite(greens[i],HIGH); 
     analogWrite(antennaeAnodes[i],brightness);
    }
  }else if (digitalRead(blueSwitch) == HIGH){
    for(int i = 0; i < 2; i++){
     digitalWrite(reds[i],HIGH);
     digitalWrite(blues[i],LOW);
     digitalWrite(greens[i],HIGH); 
     analogWrite(antennaeAnodes[i],brightness);
    }
  }else if (digitalRead(greenSwitch) == HIGH){    
    for(int i = 0; i < 2; i++){
     digitalWrite(reds[i],HIGH);
     digitalWrite(blues[i],HIGH);
     digitalWrite(greens[i],LOW); 
     analogWrite(antennaeAnodes[i],brightness);
    }
  }else if (digitalRead(purpleSwitch) == HIGH){
    for(int i = 0; i < 2; i++){
     digitalWrite(reds[i],LOW);
     digitalWrite(blues[i],LOW);
     digitalWrite(greens[i],HIGH); 
     analogWrite(antennaeAnodes[i],brightness);
    }
  }else if (digitalRead(yellowSwitch) == HIGH){
    for(int i = 0; i < 2; i++){
     digitalWrite(reds[i],LOW);
     digitalWrite(blues[i],HIGH);
     digitalWrite(greens[i],LOW); 
     analogWrite(antennaeAnodes[i],brightness);
    }
  }else{
    for(int i = 0; i < 2; i++){
     digitalWrite(reds[i],HIGH);
     digitalWrite(blues[i],LOW);
     digitalWrite(greens[i],LOW); 
     analogWrite(antennaeAnodes[i],brightness);
    }
  }
}
void graph(){
  center = constrain(center,1,7);
  }
  int maxHeight = height;

  for (int i = center - 1; i >= 0; i--){
   for (int j = maxHeight; j >= 0; j--){
    digitalWrite(greenMatrix[j],LOW); 
   }
   digitalWrite(anodes[i],HIGH);
   delay(DELAY);
   for (int k = 0; k < 8; k++){
    digitalWrite(greenMatrix[k],HIGH);
    digitalWrite(anodes[k],LOW); 
   }
   maxHeight = constrain(maxHeight - 2, 0, 7);
 }
 maxHeight = height;
  for (int i = center; i < 8; i++){
   for (int j = maxHeight; j >= 0; j--){
    digitalWrite(greenMatrix[j],LOW); 
   }
   digitalWrite(anodes[i],HIGH);
   delay(DELAY);
   for (int k = 0; k < 8; k++){
    digitalWrite(greenMatrix[k],HIGH);
    digitalWrite(anodes[k],LOW); 
   }
   maxHeight = constrain(maxHeight - 2,0,7); 
 } 
}
void threeBar(){
  int centerHeight;
  if (center == 0){
   centerHeight = abs(1 * height + 3) % 8;
 }else if (height == 0){
   centerHeight = abs(center * 1 + 3) % 8;
 }else{
   centerHeight = abs(center * height + 3) % 8;
 }
 for (int i = 0; i < 3; i++){
   digitalWrite(anodes[i],HIGH);
 }
 for (int i = 0; i <= center; i++){
   digitalWrite(threeBars[i],LOW);
 }
 delay(DELAY);
 for (int i = 0; i < 8; i++){
   digitalWrite(threeBars[i],HIGH);
   digitalWrite(anodes[i],LOW);
 }
 for (int i = 3; i < 5; i++){
   digitalWrite(anodes[i],HIGH);
 }
 for (int i = 0; i <= centerHeight; i++){
   digitalWrite(threeBars[i],LOW);
 }
  delay(DELAY);
 for (int i = 0; i < 8; i++){
   digitalWrite(threeBars[i],HIGH);
   digitalWrite(anodes[i],LOW);
 }
 for (int i = 5; i < 8; i++){
   digitalWrite(anodes[i],HIGH);
 }
 for (int i = 0; i <= height; i++){
   digitalWrite(threeBars[i],LOW);
 }
  delay(DELAY);
 for (int i = 0; i < 8; i++){
   digitalWrite(threeBars[i],HIGH);
   digitalWrite(anodes[i],LOW);
 }
}
void trace(){
 digitalWrite(anodes[center],HIGH);
 digitalWrite(greenMatrix[height],LOW);
 delay(DELAY);
 digitalWrite(anodes[center],LOW);
 digitalWrite(greenMatrix[height],HIGH);
 digitalWrite(anodes[height],HIGH);
 digitalWrite(redMatrix[center],LOW);
 delay(DELAY);
 digitalWrite(anodes[height],LOW);
 digitalWrite(redMatrix[center],HIGH);
}
