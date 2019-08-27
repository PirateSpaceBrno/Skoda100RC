#include "Arduino.h"
#include "EEPROM.h"
#include "flashLightControl.h"
#include "remoteControl.h"
#include "svetla.h"
#include "klakson.h"
#include "motor.h"

// Serial communication variables
char serialChar;
String serialCommand;
bool endLine = false;

bool sireneHonk = false;

void setupSerialCommandLine() {
  Serial.begin(9600);  
  Serial.println("--- Skoda 100 RC ---");
  Serial.println();
}

void readSerialCommand() {
  if (Serial.available() > 0)
  {
    serialChar = Serial.read();
    if(serialChar == '\n') {
      endLine = true;
    }
    else {
      serialCommand += serialChar;
    }
  }
  if (endLine) {
    Serial.println("< " + serialCommand);
    triggerSerialCommand(serialCommand);
    
    serialCommand = "";
    endLine = false;
  }
}

void triggerSerialCommand(String command) {
  if(command.equalsIgnoreCase("HELP") || command.equals("")) {
      Serial.println(">      --- Skoda 100L RC ---     ");
      Serial.println(">         GNU GPL v3 2018        ");
      Serial.println("> Pirate Space Brno, Ondrej Kotas");
      Serial.println(">");
      Serial.println("> *******************************");
      Serial.println("> * Seznam pouzitelnych prikazu *");
      Serial.println("> *******************************");
      Serial.println(">");
      Serial.println("> Ovladani svetel:");
      Serial.println("> ----------------");
      Serial.println("> SK100 - predni a zadni svetla vypnuta");
      Serial.println("> SK101 - predni a zadni svetla obrysova");
      Serial.println("> SK102 - predni a zadni svetla potkavaci");
      Serial.println("> SK103 - predni dalkova, zadni potkavaci");
      Serial.println("> SK104 - predni svetelna houkacka, zadni potkavaci");
      Serial.println("> SK110 - blinkry vypnuty");
      Serial.println("> SK111 - blinkr levy zapnut");
      Serial.println("> SK112 - blinkr pravy zapnut");
      Serial.println("> SK113 - blinkry vystrazne");
      Serial.println(">");
      Serial.println("> Motory:");
      Serial.println("> -------");
      //Serial.println("> SK200 - zvuk motoru vypnout");
      //Serial.println("> SK201 - zvuk motoru zapnout");
      //Serial.println("> SK210 - zastavit servomotor rizeni");
      //Serial.println("> SK211 XX - nastavit servomotor rizeni na uhel XX°");
      Serial.println("> SK220 - zastavit servomotor pohybu");
      Serial.println("> SK221 - otacet servomotor pohybu dopredu");
      Serial.println("> SK222 - otacet servomotor pohybu dozadu");
      Serial.println(">");
      Serial.println("> Dalsi funkce:");
      Serial.println("> -------------");
      Serial.println("> SK800 - klakson");
      Serial.println("> SK888 - spustit alarm");
      Serial.println("> SK889 - vypnout alarm");
      Serial.println(">");
      Serial.println("> Zjistovani stavu:");
      Serial.println("> -----------------");
      Serial.println("> SK900 - vrati aktualni rezim svetel");
      Serial.println("> SK910 - vrati aktualni rezim blinkru");
      Serial.println(">");
      Serial.println();
  }

  else if(command.equalsIgnoreCase("SK100")) {
    sireneEnabled = false;
    currentHeadlightsMode = VYPNUTO;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK101")) {
    sireneEnabled = false;
    currentHeadlightsMode = OBRYSOVA;
    Serial.println("> OK");
  }
  
  else if(command.equalsIgnoreCase("SK102")) {
    sireneEnabled = false;
    currentHeadlightsMode = POTKAVACI;
    Serial.println("> OK");
  }
  
  else if(command.equalsIgnoreCase("SK103")) {
    sireneEnabled = false;
    currentHeadlightsMode = DALKOVA;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK104")) {
    sireneEnabled = true;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK110")) {
    flashLeft = false;
    flashRight = false;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK111")) {
    flashLeft = true;
    flashRight = false;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK112")) {
    flashLeft = false;
    flashRight = true;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK113")) {
    flashLeft = true;
    flashRight = true;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK220")) {
    drivingMotorMode = STOP;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK221")) {
    drivingMotorMode = DOPREDU;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK222")) {
    drivingMotorMode = DOZADU;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK800")) {
    hornInterval = 1000;
    Serial.println("> OK");
  }

  else if(command.equalsIgnoreCase("SK888")) {
    alarm(false);
    Serial.println("> ALARM");
  }

  else if(command.equalsIgnoreCase("SK889")) {
    alarm(true);
    Serial.println("> NO ALARM");
  }

  else if(command.equalsIgnoreCase("SK900")) {
    if(sireneEnabled) {
      Serial.println("> Svetla: HOUKACKA");
    }
    else {
      switch (currentHeadlightsMode) {
        case OBRYSOVA:
          Serial.println("> Svetla: OBRYSOVA");
          break;
        case POTKAVACI:
          Serial.println("> Svetla: POTKAVACI");
          break;
        case DALKOVA:
          Serial.println("> Svetla: DALKOVA");
          break;
        default:
          Serial.println("> Svetla: VYPNUTO");
          break;
      }
    }
  }

  else if(command.equalsIgnoreCase("SK910")) {
      String leftState = (flashLeft ? "ZAPNUTO" : "VYPNUTO");
      String rightState = (flashRight ? "ZAPNUTO" : "VYPNUTO");
      Serial.println("> Levy blinkr: " + leftState);
      Serial.println("> Pravy blinkr: " + rightState);
  }

  else {
    Serial.println("> NEZNAMY PRIKAZ");
  }
}
