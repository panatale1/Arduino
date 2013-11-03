const int cols[] = {0,1,2,3,4,5,6,7};
const int rows[] = {8,9,10,11,12,13,14,15};
const int pot = 5;
int x;
int col1 = 0b00000001;
int col2 = 0b00000011;
int col3 = 0b00000111;
int col4 = 0b00001111;
int col5 = 0b00011111;
int col6 = 0b00111111;
int col7 = 0b01111111;
int col8 = 0b11111111;
void setup(){
 for (int i = 0; i < 8; i++){
  pinMode(cols[i],OUTPUT);
  pinMode(rows[i],OUTPUT);
  digitalWrite(rows[i],HIGH);
 } 
}

void loop(){
// readSensors();
 drawScreen();
}

void drawScreen(){
 x = 7 - map(analogRead(A5),0,1023,0,7);
 for (int i = 0; i <= x; i++){
    setCol(i,i);
    delay(2);
    for (int j = 0; j < 8; j++){
      digitalWrite(rows[j],HIGH);
      digitalWrite(cols[i],LOW);
    }
    //delay(5);
 } 
    for(int j = 0; j < 8; j++){
     digitalWrite(rows[j],HIGH);
     digitalWrite(cols[j],LOW);
   }
}

void setCol(int colSet, int rowSet){
 digitalWrite(cols[colSet],HIGH);
  for (int i = 0; i <= rowSet; i++){
   digitalWrite(rows[i],LOW);
  }
}

