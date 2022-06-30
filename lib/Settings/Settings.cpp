#include "Settings.h"
#include <Arduino.h>

void Settings::setup(void) {
  Serial.println("Setting up controller... ");
  Serial.println("Serial data rate 115200. To change controller settings send enter.");
  int time = millis();
  bool set_settings = false;
  while (/*time + 5000 < millis()*/true) {
    if (Serial.available() > 0){
      // read the incoming byte:
      int incomingByte = Serial.read();

      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte);
      set_settings = true;
      break;
    }
  }

  while (set_settings) {
    String settings_print = "Settings: \n ID: " + id ;
    settings_print += "\nSEND_FREQ: " + send_freq;
    settings_print += "\nTo change a setting input the exact name, to exit enter EXIT";
    Serial.println(settings_print);
    
    while(true){
      Serial.print("Input: ");
      if (Serial.available() > 0) {
        String input = Serial.readString();
        Serial.println(input);
        
        if (input =="ID") {
          Serial.println("Setting ID, please enter value to set id to: ");
          Serial.print("Input: ");
          if (Serial.available() > 0){
            input = Serial.readString();
            id = input.toInt();
            Serial.println(input);
            break;
          }
        }
        if (input =="SEND_FREQ"){
          Serial.println("Setting SEND_FREQ, please enter value to set id to: ");
          Serial.print("Input: ");
          if (Serial.available() > 0){
            input = Serial.readString();
            send_freq = input.toInt();
            Serial.println(input);
            break;
          }
        }
        if (input == "EXIT" ) {
            Serial.println("Exiting Settings");
            set_settings = false;
            break;
        }
      }
    }
  }

}