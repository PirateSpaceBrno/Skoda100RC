#include "svetla.h"

int button = 3;
int buttonValue = 0;

void setup()
{
  setupLights();
  
  pinMode(button, INPUT);

  digitalWrite(button, HIGH);       // turn on pullup resistor
}

void loop()
{
  buttonValue = digitalRead(button);
  
  buttonValue ? controlLights(DALKOVA) : controlLights(OBRYSOVA);
  //buttonValue ? controlBlinkLights(false, false) : controlBlinkLights(true, true);
  
  //controlLights(OBRYSOVA);
  //delay(5000);
  //controlLights(POTKAVACI);
  //delay(5000);
  //controlLights(DALKOVA);
  //delay(5000);
  //controlLights(POTKAVACI);
  //delay(5000);
  //controlLights(OBRYSOVA);
  //delay(5000);
  
  controlBlinkLights(true, true);
}




