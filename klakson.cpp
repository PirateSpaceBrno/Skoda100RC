#include "Arduino.h"
#include "klakson.h"
#include "svetla.h"

int hornPin = 8;
int lastHornForce = 0;
int hornInterval = 0;
unsigned long lastHonk = 0;
bool hornOscillate = false;
unsigned long lastAlarmHonk = 0;
bool alarmOn = false;

void controlHorn() {
    unsigned long currentHonk = millis();
    
    if(lastHornForce == 0 && hornInterval > 0) {
        lastHonk = currentHonk;
        //digitalWrite(hornPin, HIGH);
        lastHornForce = 255;
        analogWrite(hornPin, lastHornForce);
        //Serial.println("KLAKSON");
    }
    else {
      if(hornInterval > 0 && (unsigned long)(currentHonk - lastHonk) >= hornInterval) {
        if(hornOscillate == false) {
          hornInterval = 0;  
        }
        //digitalWrite(hornPin, LOW);
        lastHornForce = 0;
        analogWrite(hornPin, lastHornForce);
      }
    }
}


void setupHorn() {
  pinMode(hornPin, OUTPUT);
  //digitalWrite(hornPin, HIGH);
  lastHornForce = 0;
}

void alarm(bool turnOff) {
  if(turnOff) {
    alarmOn = false;
    flashLeft = false;
    flashRight = false;
  }
  else {
    alarmOn = true;
  }
}

void controlAlarm() {
  if(alarmOn) {
    unsigned long currentHonk = millis();
    
    if((unsigned long)(currentHonk - lastAlarmHonk) >= 1000) {
      sireneEnabled = true;
      flashLeft = true;
      flashRight = true;
      hornInterval = 500;
      lastAlarmHonk = currentHonk;
    }
  }
}

