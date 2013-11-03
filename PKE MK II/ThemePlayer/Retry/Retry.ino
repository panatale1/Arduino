int speakerPin = 12;
int length = 9;
char notes[] = "bbdDfaaee";
int beats[] = {2,2,1,1,2,2,2,2,2};
int tempo = 300;
boolean played = false;
void playTone(int tone_, int duration){
  for(long i = 0; i < duration * 1000L; i+= tone_*2){
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone_);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(tone_);
  }
}
void playNote(char note, int duration){
  char names[] = {'b','d','D','f','a','e'};
  int tones[] = {988,1175,1245,1397,1760,1319};
  for(int i = 0; i < 6; i++){
    if(names[i]==note){
      playTone(tones[i],duration);
    }
  }
}

void setup(){
  pinMode(speakerPin,OUTPUT);
}
void loop(){
  if (!played){
  for (int i = 0; i < length; i++){
    if(notes[i] == ' '){
      delay(beats[i]*tempo);
    }else{
      playNote(notes[i],beats[i]*tempo);
    }
    delay(tempo/2);
  }
  played = true;
  }
}
