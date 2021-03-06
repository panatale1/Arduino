//#include "pitches.h"

const int NOTE_B = 988;
const int NOTE_D = 1175;
const int NOTE_DS = 1245;
const int NOTE_F = 1397;
const int NOTE_A = 1760;
const int NOTE_E = 1319;
const int restCount = 100;
const int speakerOut = 11;
boolean played = false;
//const int NOTE_B0 = 31;
//const int NOTE_E1 = 41;
//const int NOTE_F1 = 44;
//const int NOTE_G1 = 49;
//const int NOTE_A1 = 55;
const int melody2[] = {NOTE_B,NOTE_B,NOTE_D,NOTE_DS,NOTE_F,NOTE_A,NOTE_A, NOTE_E, NOTE_E};
const int beats2[] = {2,2,1,1,2,2,2,2,2};
//const int melody[] = {d,d,f,fSharp,a,c,b,d,d,f,fSharp,a,c,b,b,b,dSharp,b,cSharp,aSharp,R,R,b,b,b,b,aSharp,cSharp,b,R,b,b,b,dSharp,b,cSharp,aSharp,R,R,b,b,b,b,aSharp,cSharp,b,R};
const int beats[] = {2,2,1,1,2,4,4,2,2,1,1,2,4,4,1,2,2,2,2,2,2,1,1,1,1,2,2,2,2,4,4,1,2,2,2,2,2,2,1,1,1,1,2,2,2,3};

int pause = 1000;
long tempo = 150000;

int tone_ = 0;
int beat = 0;
long duration = 0;

void setup(){
  pinMode(speakerOut,OUTPUT);
//  pinMode(12,OUTPUT);
  //digitalWrite(12,LOW);
  Serial.begin(9600);
}
void loop(){
  if (!played){
    for (int i = 0; i < 9; i++){
      tone_ = melody2[i];
      beat = beats2[i];
      duration = beat * tempo;
      playTone();
      delayMicroseconds(pause);
      Serial.println(tone_);
      Serial.println(duration);
      played = true;
    }
  }
}
void playTone(){
 long elapsed = 0;
 if (tone_ != 0){
   while (elapsed < duration){
    digitalWrite(speakerOut,HIGH);
    delayMicroseconds(1/(tone_*2));
    digitalWrite(speakerOut,LOW);
    delayMicroseconds(1/(tone_*2));
    elapsed += tone_;
   }
  }
  else{
    for (int i = 0; i < restCount; i++){
      delayMicroseconds(duration);
    }
  }
}

