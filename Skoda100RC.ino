#include "flashLightControl.h"
#include "remoteControl.h"
#include "svetla.h"
#include "klakson.h"
#include "motor.h"
#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;


// Main program
void setup()
{
  setupLights();
  setupHorn();
  setupSerialCommandLine();
  //setupMotors();
  
  //IRREmote
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

HeadlightsMode lastHeadlightsMode = VYPNUTO;
HeadlightsMode lastHeadlightsMode1 = VYPNUTO;
void loop()
{
  // Inner infinite cycle to improve timing
  while(1){
    // Control lights
    controlLights();

    // Control sound
    controlHorn();
    controlAlarm();

    //controlDrivingMotor();
  
    // Read commands from serial line
    readSerialCommand();

    if (irrecv.decode(&results)){
          //Serial.println(results.value, HEX);
          //2155855935 // on/off
          if(results.value == 2155855935) {
            switch(currentHeadlightsMode) {
              case POTKAVACI:
                lastHeadlightsMode = currentHeadlightsMode;
                currentHeadlightsMode = OBRYSOVA;
                triggerSerialCommand("SK900");
                break;
              case VYPNUTO:
                lastHeadlightsMode = currentHeadlightsMode;
                currentHeadlightsMode = OBRYSOVA;
                triggerSerialCommand("SK900");
                break;
              default:
                if(lastHeadlightsMode == VYPNUTO) {
                  lastHeadlightsMode = currentHeadlightsMode;
                  currentHeadlightsMode = POTKAVACI;
                  triggerSerialCommand("SK900");
                }
                else {
                  lastHeadlightsMode = currentHeadlightsMode;
                  currentHeadlightsMode = VYPNUTO;
                  triggerSerialCommand("SK900");
                }
                break;
            }
          }
          //2155860015 // timer
          if(results.value == 2155860015) {
            alarmOn ? triggerSerialCommand("SK889") : triggerSerialCommand("SK888");
          }
          //2155864095 // speed
          if(results.value == 2155864095) {
            if(flashRight) {
              flashRight = false;
            }
            else {
              flashRight = true;
            }
            triggerSerialCommand("SK910");
          }
          //2155857975 // osc
          if(results.value == 2155857975) {
            if(currentHeadlightsMode == DALKOVA) {
              currentHeadlightsMode = lastHeadlightsMode1;
              triggerSerialCommand("SK900");
            }
            else {
              lastHeadlightsMode1 = currentHeadlightsMode;
              currentHeadlightsMode = DALKOVA;
              triggerSerialCommand("SK900");
            }
          }
          //2155868175 // mode
          if(results.value == 2155868175) {
            if(flashLeft) {
              flashLeft = false;
            }
            else {
              flashLeft = true;
            }
            triggerSerialCommand("SK910");
          }
          
          irrecv.resume();
    }
  }
}






