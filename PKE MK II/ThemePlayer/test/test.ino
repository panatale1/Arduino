#include "pitches.h"

const int melody[] = {NOTE_A5,NOTE_B5,NOTE_C6,NOTE_D6,NOTE_E6,NOTE_F6,NOTE_G6};
const int beats[] = {1,1,1,1,1,1,1};
int pause = 1000;
long tempo = 150000;
int tone_ = 0;
int beat = 0;
long duration = 0;
boolean played = false;
void setup(){
 pinMode(11,OUTPUT); 
}

void loop(){
  if (!played){
    for (int i = 0; i < 7; i++){
      tone_ = melody[i];
      beat = beats[i];
      duration = beat * tempo;
      playTone();
      delayMicroseconds(pause);
    }
    for (int i = 6; i >= 0; i--){
      tone_ = melody[i];
      beat = beats[i];
      duration = beat * tempo;
      playTone();
      delayMicroseconds(pause);
    }
    played = true;
  }
}
void playTone(){
  long elapsed = 0;
  while (elapsed < duration){
    digitalWrite(11,HIGH);
    delayMicroseconds(tone_/2);
    digitalWrite(11,LOW);
    delayMicroseconds(tone_/2);
    elapsed += tone_;
  }
}
