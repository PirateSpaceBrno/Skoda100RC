#include "Arduino.h"
#include "svetla.h"
#include "klakson.h"

// LED lights pinout
int headlights = 10;
int rightBlinkr = 20;
int leftBlinkr = 19;
//int rearlights = 0;
//int brakelights = 0;
//int reverselights = 0;
//int platelight = 0;

// Other variables
unsigned long blinkInterval = 400;
unsigned long blinkOffInterval = 200;
unsigned long lastBlink = 0;
int lastBlinkForce = 0;

unsigned long sireneBlinkInterval = 125;
unsigned long lastSireneBlink = 0;
HeadlightsMode lastSireneBlinkForce = VYPNUTO;
int sireneMaxRepeat = 2;
int sireneRepeated = 0;

HeadlightsMode currentHeadlightsMode = VYPNUTO;
bool sireneEnabled = false;
bool flashLeft = false;
bool flashRight = false;


// Methods
void controlBlinkLights() {
  if(flashLeft || flashRight) {
    unsigned long currentBlink = millis();

    if(lastBlinkForce == 0) {
      if((unsigned long)(currentBlink - lastBlink) >= blinkOffInterval) {
          lastBlink = currentBlink;
  
          lastBlinkForce = 255;
      }  
    }
    else {
      if((unsigned long)(currentBlink - lastBlink) >= blinkInterval) {
          lastBlink = currentBlink;
  
          lastBlinkForce = 0;
      }      
    }

    flashLeft ? analogWrite(leftBlinkr, lastBlinkForce) : analogWrite(leftBlinkr, 0);
    flashRight ? analogWrite(rightBlinkr, lastBlinkForce) : analogWrite(rightBlinkr, 0);      
  }
  else {
    analogWrite(leftBlinkr, 0);
    analogWrite(rightBlinkr, 0);      
  }
}

void changeLightsMode(HeadlightsMode mode) {
  switch (mode) {
    case OBRYSOVA:
      currentHeadlightsMode = OBRYSOVA;
      analogWrite(headlights, 1);
      //analogWrite(rearlights, 1);
      //analogWrite(platelight, 255);
      break;
    case POTKAVACI:
      currentHeadlightsMode = POTKAVACI;
      analogWrite(headlights, 50);
      //analogWrite(rearlights, 50);
      //analogWrite(platelight, 255);
      break;
    case DALKOVA:
      currentHeadlightsMode = DALKOVA;
      analogWrite(headlights, 255); // 255 is maximum value
      break;
    case HOUKACKA:    
      analogWrite(headlights, 255); // 255 is maximum value
      break;
    default:
      currentHeadlightsMode = VYPNUTO;
      analogWrite(headlights, 0);
      //analogWrite(rearlights, 0);
      //analogWrite(platelight, 0);
      break;
  }
}

void controlHeadLights() {
  unsigned long currentBlink = millis();

  if(sireneEnabled) {
    if((unsigned long)(currentBlink - lastSireneBlink) >= sireneBlinkInterval) {
        lastSireneBlink = currentBlink;
        
        if(lastSireneBlinkForce == VYPNUTO) {
          lastSireneBlinkForce = HOUKACKA;
         
          if(sireneRepeated == sireneMaxRepeat) {
            sireneEnabled = false;
          }
          else {
            changeLightsMode(lastSireneBlinkForce);
            sireneRepeated = sireneRepeated + 1;
          }
        }
        else {
          lastSireneBlinkForce = VYPNUTO;
          changeLightsMode(currentHeadlightsMode);
        }
    }
  }
  else {
    sireneEnabled = false;
    sireneRepeated = 0;
    lastSireneBlinkForce = VYPNUTO;
    changeLightsMode(currentHeadlightsMode);
  }
}

void controlBrakeLights() {
  //glowBrake ? analogWrite(brakelights, 255) : analogWrite(brakelights, 0);
}

void controlReverseLights() {
  //glowBrake ? analogWrite(brakelights, 255) : analogWrite(brakelights, 0);
}

void controlLights() {
  controlHeadLights();
  controlBlinkLights();
  //controlBrakeLights();
  //controlReverseLights();
}

void setupLights() {
  // Set all lights pins
  pinMode(headlights, OUTPUT);
  pinMode(leftBlinkr, OUTPUT);
  pinMode(rightBlinkr, OUTPUT);
  //pinMode(rearlights, OUTPUT);
  //pinMode(brakelights, OUTPUT);
  //pinMode(reverselights, OUTPUT);
  //pinMode(platelight, OUTPUT);

  // Turn off all the lights
  analogWrite(headlights, 0);
  analogWrite(leftBlinkr, 0);
  analogWrite(rightBlinkr, 0);
  //analogWrite(rearlights, 0);
  //analogWrite(brakelights, 0);
  //analogWrite(reverselights, 0);
  //analogWrite(platelight, 0);
}

