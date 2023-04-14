#include "Settings.h"


void Settings::setup() {
  Serial.println("Setting up controller... ");
  preferences.begin("app", false);

  update_variables();
  print_settings();
  Serial.println("To change controller settings send anything.");


  unsigned long time = millis();
  bool set_settings = false;

  while (set_settings || millis() < time + 2000) {

    if (millis() < time + 2000) { // check for input
      if (Serial.available() > 0){
        set_settings = true;
        String del = Serial.readString(); // clear buffer
      } else continue;

    } else {
      print_settings();
      Serial.print("To change a setting (Only settings with only uppercase letters), \ninput the exact name followed by a space and the new value, to exit enter EXIT: ");
      while (Serial.available() == 0) {delay(1);} // wait for input
    }
    
    String input = Serial.readString();
    input.toUpperCase();
    Serial.println(input);
    
    

    for (int i=0; i<sizeof(settings)/sizeof(*settings); ++i) {
      if (input.startsWith(settings[i][0])) {
        int index = input.indexOf(" ");
        if (index != -1) {
          int value = input.substring(index+1).toInt();
          input.remove(index);
          preferences.putInt(input.c_str(), value);
          update_variables();
        } else {
          Serial.println("Value or space not found in: " + input);
        }
        break;
      }
    }
    if (input.startsWith("EXIT")) {
      Serial.println("Exiting Settings...");
      set_settings = false;
    }
  }
  print_settings();
}

void Settings::update_variables() {
  ID = preferences.getInt(settings[0][0].c_str(), ID);
  SEND_FREQ = preferences.getInt(settings[1][0].c_str(), SEND_FREQ);
  OFF_TIME = preferences.getInt(settings[2][0].c_str(), OFF_TIME);
  OFF_THRESHOLD = preferences.getInt(settings[3][0].c_str(), OFF_THRESHOLD);
  BUF_LEN = preferences.getInt(settings[4][0].c_str(), BUF_LEN);
  CONTROLLER_MODE = preferences.getString("mode", CONTROLLER_MODE);
  TOPVAL_MAT =  preferences.getInt(settings[5][0].c_str(), TOPVAL_MAT);
  TOPVAL_RIBBON =  preferences.getInt(settings[6][0].c_str(), TOPVAL_RIBBON);
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