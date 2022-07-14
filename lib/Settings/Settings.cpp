#include "Settings.h"


void Settings::preference_setup(){
  preferences.begin("app", false);

  id = preferences.getInt("ID", 0);
  send_freq = preferences.getInt("SEND_FREQ", 50);
  shutdown_time = preferences.getInt("SHUTDOWN_TIME", 300);
  shutdown_threshold = preferences.getInt("SHUTDOWN_THRESHOLD", 400);
  mode = preferences.getString("mode", "BLE_VALUES");
  print_settings();
}


void Settings::setup() {
  Serial.println("Setting up controller... ");
  preference_setup();
  Serial.println("To change controller settings send anything.");
  int time = millis();
  bool set_settings = false;
  while (millis() < time + 2000) {
    if (Serial.available() > 0){
      while(Serial.available() > 0){
        Serial.read();
      }
      set_settings = true;
      break;
    }
  }

  while (set_settings) {
    print_settings();
    Serial.print("To change a setting (Only settings with only uppercase letters), input the exact name, to exit enter EXIT: ");

    while (Serial.available() == 0) {delay(1);} // wait for input
    String input = Serial.readString();
    Serial.println(input);
    
    if (input =="ID") {
        id = change_setting(input);

    } else if (input =="SEND_FREQ"){
        send_freq = change_setting(input, " in ms");

    } else if (input =="SHUTDOWN_TIME"){
        shutdown_time = change_setting(input, " in s");

    } else if (input =="SHUTDOWN_THRESHOLD"){
        shutdown_threshold = change_setting(input, " between 0 and 4096");

    } else if (input =="BUF_LEN"){
        buf_len = change_setting(input);

    } else if (input == "EXIT" ) {
        Serial.println("Exiting Settings...");
        set_settings = false;
    } else {
      Serial.println("Entered setting not found please try again.");
    }
  }
}


int Settings::change_setting(String input, String unit){
  Serial.print("Setting " + input + unit +", please enter new value: ");
  while (Serial.available() == 0) {delay(1);} // wait for input
  int value = Serial.readString().toInt();
  Serial.println(value);
  preferences.putInt(input.c_str(), value);
  return value;
}


void Settings::print_settings(){
  Serial.println("Controller Settings: "
    "\n Data Rate:          " + String(115200) + 
    "\n Mode:               " + String(mode) + 
    "\n ID:                 " + String(id) + 
    "\n SEND_FREQ:          " + String(send_freq) + 
    "\n SHUTDOWN_TIME:      " + String(shutdown_time) + 
    "\n SHUTDOWN_THRESHOLD: " + String(shutdown_threshold)
  );
}


void Settings::save_mode(String mode_){
  preferences.putString("mode", mode_);
  mode = mode_;
}