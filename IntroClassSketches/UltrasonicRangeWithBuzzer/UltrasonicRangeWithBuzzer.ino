/*******************************************************************
*  This was one of the hard examples for an Intro to Arduino class
*  taught at the Greenburgh Public Library on Aug. 11, 2016.
*  This takes an Arduino board, connects an ultrasonic range finder
*  to pin 3 as well as to Ground and 5V, and connects a piezo
*  buzzer to pin 9 (a PWM pin) and to ground. It then defines the
*  class required to use the ultrasonic range fnder and its component
*  members. In the loop method, it makes the pitch of the buzzer
*  lower or raise the closer or further the range finder detects
*  an item.
*******************************************************************/
#include "Arduino.h"

class Ultrasonic {
    public:
        Ultrasonic(int pin);
        void DistanceMeasure(void);
        long microsecondsToCentimeters(void);
    private:
        int _pin;
        long duration;
    };

Ultrasonic::Ultrasonic(int pin) {
    _pin = pin;
}

void Ultrasonic::DistanceMeasure(void) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_pin, LOW);
    pinMode(_pin, INPUT);
    duration = pulseIn(_pin, HIGH);
}

long Ultrasonic::microsecondsToCentimeters(void) {
    return duration / 29 / 2;
}

Ultrasonic ranger(3);
int buzzer = 0;
long rangeInCm;
int pulse;

void setup() {
    pinMode(buzzer, OUTPUT);
}

void loop(){
    ranger.DistanceMeasure();
    rangeInCm = ranger.microsecondsToCentimeters();
    pulse = map(rangeInCm, 1.2, 156, 0, 255);
    analogWrite(buzzer, pulse);
    delay(250);
}
