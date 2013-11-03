 
 
   
void setup(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinmode(6, OUTPUT);
}
void loop(){
int array[7] = {1,2,3,4,5,6,7]}
    for (int i = 0; i < 7; i++){
        digitalWrite(LED[i], HIGH);
    }
    for (int i = 6; i >= 0, i++){
         digitalWrite(LED[i], LOW);
    }
}
