#include "Settings.h"


void Settings::setup() {
  Serial.println("Setting up controller... ");
  preferences.begin("app", false);

  read_from_memory();
  print_settings();
  Serial.println("To change controller settings send anything.");


  unsigned long time = millis();
  bool set_settings = false;

  while (set_settings || millis() < time + 2000) {

    if (millis() < time + 2000) { // check for input
      if (Serial.available() > 0){
        set_settings = true;
        Serial.readString(); // clear buffer
      } else continue;

    } else {
      print_settings();
      Serial.print("To change a setting (Only settings with only uppercase letters), \ninput the exact name followed by a space and the new value, to exit enter EXIT: ");
      while (Serial.available() == 0) {delay(1);} // wait for input
    }
    
    // read input
    String input = Serial.readString();
    input.toUpperCase();
    Serial.println(input);
    
    // iterate through all settings
    for (int i=0; i<sizeof(settings)/sizeof(*settings); ++i) {
      // check for match 
      if (input.startsWith(settings[i][0])) {
        int index = input.indexOf(" ");
        if (index != -1) {
          // extract value from input string
          int value = input.substring(index+1).toInt();
          // save new value to memory
          preferences.putInt(settings[i][0].c_str(), value);
          read_from_memory();
        } else {
          Serial.println("Value or space not found in: " + input);
        }
        break;
      }
    }
    if (input.startsWith("DEFAULT")) {
      change_settings_to_default();
    }
    else if (input.startsWith("EXIT")) {
      Serial.println("Exiting Settings...");
      set_settings = false;
    }
  }
  print_settings();
}

void Settings::read_from_memory() {
  CONTROLLER_MODE = preferences.getString("mode", CONTROLLER_MODE);
  
  ID = preferences.getInt(settings[0][0].c_str(), ID);
  SEND_FREQ = preferences.getInt(settings[1][0].c_str(), SEND_FREQ);
  OFF_TIME = preferences.getInt(settings[2][0].c_str(), OFF_TIME);
  OFF_THRESHOLD = preferences.getInt(settings[3][0].c_str(), OFF_THRESHOLD);
  BUF_LEN = preferences.getInt(settings[4][0].c_str(), BUF_LEN);
  TOPVAL_MAT =  preferences.getInt(settings[5][0].c_str(), TOPVAL_MAT);
  TOPVAL_RIBBON =  preferences.getInt(settings[6][0].c_str(), TOPVAL_RIBBON);
}

void Settings::change_settings_to_default() {
  Serial.println("Changing values to default");
  for (int i=0; i<sizeof(settings)/sizeof(*settings); ++i) {
    if (preferences.getInt(settings[i][0].c_str(), 0) == 0) {
      preferences.putInt(settings[i][0].c_str(), settings[i][2].toInt());
    }
  }
}

void Settings::print_settings() {
  Serial.println("Controller Settings: "
    "\n Data Rate               " + String(115200) + 
    "\n Mode                    " + String(CONTROLLER_MODE)
  );
  for (int i=0; i<sizeof(settings)/sizeof(*settings); ++i) {
    char print_buffer[100];
    sprintf(print_buffer, " %-20s  %-5d  %s",
      settings[i][0], preferences.getInt(settings[i][0].c_str(), 0), settings[i][1]
    );
    Serial.println(print_buffer);
  }
}


void Settings::save_mode(String mode_) {
  preferences.putString("mode", mode_);
  CONTROLLER_MODE = mode_;
}