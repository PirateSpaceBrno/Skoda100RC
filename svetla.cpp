#include "Arduino.h"
#include "svetla.h"

// LED lights pinout
int headlights = 11;
int rightBlinkr = 8;
int leftBlinkr = 12;

// Other variables
unsigned long lastBlink = 0;
int lastBlinkForce = 0;
unsigned long blinkInterval = 400;

// Methods
void controlBlinkLights(bool left = false, bool right = false) {
  unsigned long currentBlink = millis();
    
    if((unsigned long)(currentBlink - lastBlink) >= blinkInterval) {
        lastBlink = currentBlink;

        lastBlinkForce = (lastBlinkForce == 0) ? 255 : 0;

        left ? analogWrite(leftBlinkr, lastBlinkForce) : analogWrite(leftBlinkr, 0);
        right ? analogWrite(rightBlinkr, lastBlinkForce) : analogWrite(rightBlinkr, 0);
    }
}

void controlLights(headlightsMode mode) {
  switch (mode) {
    case OBRYSOVA:
      analogWrite(headlights, 1);
      break;
    case POTKAVACI:
      analogWrite(headlights, 75);
      break;
    case DALKOVA:
      analogWrite(headlights, 255);
      break;
    default:
      analogWrite(headlights, 0);
      break;
  }
}

void setupLights() {
  // Set all lights pins
  pinMode(headlights, OUTPUT);
  pinMode(leftBlinkr, OUTPUT);
  pinMode(rightBlinkr, OUTPUT);

  // Turn off all the lights
  analogWrite(headlights, 0);
  analogWrite(leftBlinkr, 0);
  analogWrite(rightBlinkr, 0);
}

