//Declare anodes and cathodes for display
const int screenAnodes[] = {23,25,27,29,31,33,35,37};
const int greenScreen[] = {24,28,32,36,40,44,48,52};
const int redScreen[] = {22,26,30,34,38,42,46,50};
const int threeBars[] = {24,28,32,36,40,42,46,50};
//Declare input pins to control screen mode change
const int modePin1 = 2;
const int modePin2 = 3;
//Declare input pins to control antennae colors
const int redSwitch = 17;
const int greenSwitch = 18;
const int blueSwitch = 19;
const int yellowSwitch = 20;
const int purpleSwitch = 21;
//Declare the anode and cathodes for antennae
const int antennaeAnodes = 45;
const int antennaeRed = 41;
const int antennaeBlue = 43;
const int antennaeGreen = 47;
//declare input pins for potentiometers
const int dimmerPot = 7;
const int horizontalPot = 6;
const int verticalPot = 5;
//Declare the blink delay as 2 milliseconds
const int DELAY = 2;
//Declare screenMode as volatile because
//it is changed in an interrupt sequence
volatile int screenMode = 0;
//ints to hold the values from the potentiometers
int center, height, brightness;

void setup(){
  //Set up the display anodes for output
  for (int i = 0; i < 8; i++){
   pinMode(screenAnodes[i],OUTPUT); 
  }
  //Set up all the cathodes for the display as output
  for (int i = 22; i < 53; i +=2){
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  //Set the antennae anodes and cathodes for output
  pinMode(antennaeAnodes,OUTPUT);
  pinMode(antennaeRed,OUTPUT);
  pinMode(antennaeBlue,OUTPUT);
  pinMode(antennaeGreen,OUTPUT);
  //Set up the input switches to control the antennae color
  pinMode(redSwitch,INPUT);
  pinMode(blueSwitch,INPUT);
  pinMode(greenSwitch,INPUT);
  pinMode(purpleSwitch,INPUT);
  pinMode(yellowSwitch,INPUT);
  //Call the sequence to set the antennae color
  colorSwitch();
  //Set up the input switches to control display mode
  pinMode(modePin1,INPUT);
  pinMode(modePin2,INPUT);
  //Call the sequence to set the display mode
  screenSwitch();
  //Attach interrupt sequences to interrupt pins
  
  //If either INT0 or INT1 are triggered,
  //execute screenSwitch()
  attachInterrupt(0,screenSwitch,CHANGE);
  attachInterrupt(1,screenSwitch,CHANGE);
  //If INT2, INT3, or INT4 are triggered
  //execute colorSwitch()
  attachInterrupt(2,colorSwitch,CHANGE);
  attachInterrupt(3,colorSwitch,CHANGE);
  attachInterrupt(4,colorSwitch,CHANGE);
}

void loop(){
  //Read the potentiometers
  
  //Map the dimmer pot from a 1024 range to a 256 range
  brightness = map(analogRead(dimmerPot),0,1023,0,255);
  //Map the positional pots from 1024 to 8
  center = map(analogRead(horizontalPot),0,1023,0,7);
  height = map(analogRead(verticalPot),0,1023,0,7);
  //Write the brightness of the antennae
  analogWrite(antennaeAnodes,brightness);
  //Read screenMode from RAM and choose which screen mode to execute 
  if (screenMode == 0){
    graph();
  }else if (screenMode == 1){
    threeBar();
  }else{
    trace();
  }
}
//Interrupt sequence to select antennae color
void colorSwitch(){
  //Read which switch is high, and adjust cathodes as required
  if (digitalRead(redSwitch) == HIGH){
   digitalWrite(antennaeRed,LOW);
   digitalWrite(antennaeGreen,HIGH);
   digitalWrite(antennaeBlue,HIGH); 
  }else if (digitalRead(blueSwitch) == HIGH){
    digitalWrite(antennaeBlue,LOW);
    digitalWrite(antennaeRed,HIGH);
    digitalWrite(antennaeGreen,HIGH); 
  }else if (digitalRead(greenSwitch) == HIGH){
   digitalWrite(antennaeGreen,LOW);
   digitalWrite(antennaeRed,HIGH);
   digitalWrite(antennaeBlue,HIGH); 
  }else if (digitalRead(purpleSwitch) == HIGH){
   digitalWrite(antennaeBlue,LOW);
   digitalWrite(antennaeRed,LOW);
   digitalWrite(antennaeGreen,HIGH); 
  }else if (digitalRead(yellowSwitch) == HIGH){
   digitalWrite(antennaeGreen,LOW);
   digitalWrite(antennaeRed,LOW);
   digitalWrite(antennaeBlue,HIGH);
  }else{
   digitalWrite(antennaeBlue,LOW);
   digitalWrite(antennaeGreen,LOW);
   digitalWrite(antennaeRed,HIGH); 
  }
}
//Interrupt sequence for screen display
void screenSwitch(){
  //Read which mode pin is high, and change selector accordingly
  if (digitalRead(modePin1) == HIGH){
    screenMode = 0;
  }else if (digitalRead(modePin2) == HIGH){
    screenMode = 1;
  }else{
    screenMode = 2;
  }
}
//Display code for Ghostbusters: The Video Game style display
void graph(){
  //Constrain the center location to not go below 1
  center = constrain(center,1,7);
  //Set a new value equal to height to not lose height value
  int maxHeight = height;

  //Loop over the bars to the left of the maximum
  for (int i = center - 1; i >= 0; i--){
   //Loop over each of the LEDs in the column
   for (int j = maxHeight; j >= 0; j--){
    //Write the cathodes LOW
    digitalWrite(greenScreen[j],LOW); 
   }
   //Write the anodes HIGH
   digitalWrite(screenAnodes[i],HIGH);
   //Delay 2 milliseconds for persistance of vision
   delay(DELAY);
   //Reset the screen
   for (int k = 0; k < 8; k++){
    digitalWrite(greenScreen[k],HIGH);
    digitalWrite(screenAnodes[k],LOW); 
   }
   //Decrease maxHeight, making sure it doesn't go below 0
   maxHeight = constrain(maxHeight - 2, 0, 7);
 }
 //Reset maxHeight
 maxHeight = height;
 //Iterate over the bars to the right starting with center
  for (int i = center; i < 8; i++){
   for (int j = maxHeight; j >= 0; j--){
    digitalWrite(greenScreen[j],LOW); 
   }
   digitalWrite(screenAnodes[i],HIGH);
   delay(DELAY);
   for (int k = 0; k < 8; k++){
    digitalWrite(greenScreen[k],HIGH);
    digitalWrite(screenAnodes[k],LOW); 
   }
   maxHeight = constrain(maxHeight - 2,0,7); 
 }
}
//Display code for Extreme Ghostbusters-style display
void threeBar(){
  //Define the height of the center bar
  int centerHeight;
  if (center == 0){
   centerHeight = abs(1 * height + 3) % 8;
 }else if (height == 0){
   centerHeight = abs(center * 1 + 3) % 8;
 }else{
   centerHeight = abs(center * height + 3) % 8;
 }
 //Write the left column anodes HIGH
 for (int i = 0; i < 3; i++){
   digitalWrite(screenAnodes[i],HIGH);
 }
 //Write the left column cathodes LOW
 for (int i = 0; i <= center;i++){
   digitalWrite(threeBars[i],LOW);
 }
 delay(DELAY);
 //Blank the screen
  for (int i = 0; i < 8; i++){
   digitalWrite(threeBars[i],HIGH);
   digitalWrite(screenAnodes[i],LOW);
 }
 //Write the center bar anodes HIGH
 for (int i = 3; i < 5; i++){
   digitalWrite(screenAnodes[i],HIGH);
 }
 //Write the cathodes for the center bar HIGH
 for (int i = 0; i <= centerHeight; i++){
   digitalWrite(threeBars[i],LOW);
 }
  delay(DELAY);
 //Blank the screen
 for (int i = 0; i < 8; i++){
   digitalWrite(threeBars[i],HIGH);
   digitalWrite(screenAnodes[i],LOW);
 }
 //Write the right column anodes HIGH
 for (int i = 5; i < 8; i++){
   digitalWrite(screenAnodes[i],HIGH);
 }
 //Write the right column cathodes LOW
 for (int i = 0; i <= height; i++){
   digitalWrite(threeBars[i],LOW);
 }
  delay(DELAY);
  //Blank the screen
 for (int i = 0; i < 8; i++){
   digitalWrite(threeBars[i],HIGH);
   digitalWrite(screenAnodes[i],LOW);
 } 
}
//Display code for X/Y dot tracing
void trace(){
 //Write the green dot HIGH
 digitalWrite(screenAnodes[center],HIGH);
 digitalWrite(greenScreen[height],LOW);
 delay(DELAY);
 //Blank the screen
 digitalWrite(screenAnodes[center],LOW);
 digitalWrite(greenScreen[height],HIGH);
 //Write the red dot HIGH
 digitalWrite(screenAnodes[height],HIGH);
 digitalWrite(redScreen[center],LOW);
 delay(DELAY);
 //Blank the screen
 digitalWrite(screenAnodes[height],LOW);
 digitalWrite(redScreen[center],HIGH);
}
