#include "Settings.h"


void Settings::setup() {
  Serial.println("Setting up controller... ");
  preferences.begin("app", false);

  ID = preferences.getInt("ID", ID);
  SEND_FREQ = preferences.getInt("SEND_FREQ", SEND_FREQ);
  SHUTDOWN_TIME = preferences.getInt("SHUTDOWN_TIME", SHUTDOWN_TIME);
  SHUTDOWN_THRESHOLD = preferences.getInt("SHUTDOWN_THRESHOLD", SHUTDOWN_THRESHOLD);
  BUF_LEN = preferences.getInt("BUF_LEN", BUF_LEN);
  SENSOR_MODE = preferences.getString("SENSOR_MODE", SENSOR_MODE);
  CONTROLLER_MODE = preferences.getString("mode", CONTROLLER_MODE);

  print_settings();
  Serial.println("To change controller settings send anything.");
  unsigned long time = millis();
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
    input.toUpperCase();
    Serial.println(input);
    
    if (input.equals("ID")) {
        ID = change_setting(input);

    } else if (input.equals("SEND_FREQ")){
        SEND_FREQ = change_setting(input, " in ms");

    } else if (input.equals("SHUTDOWN_TIME")){
        SHUTDOWN_TIME = change_setting(input, " in s");

    } else if (input.equals("SHUTDOWN_THRESHOLD")){
        SHUTDOWN_THRESHOLD = change_setting(input, " between 0 and 4096");

    } else if (input.equals("BUF_LEN")){
        BUF_LEN = change_setting(input);

    } else if (input.equals("SENSOR_MODE")){
        Serial.print("Setting SENSOR_Mode, please enter new mode: Mat or Ribbon ");
        while (Serial.available() == 0) {delay(1);} // wait for input
        String value = Serial.readString();
        Serial.println(value);
        if (value == "Mat" || "Ribbon") {
          preferences.putString(input.c_str(), value);
          SENSOR_MODE = value;
        } else Serial.println("Not correct try again");

    } else if (input.equals("EXIT")) {
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
    "\n Mode:               " + String(CONTROLLER_MODE) + 
    "\n ID:                 " + String(ID) + 
    "\n SEND_FREQ:          " + String(SEND_FREQ) + 
    "\n SHUTDOWN_TIME:      " + String(SHUTDOWN_TIME) + 
    "\n SHUTDOWN_THRESHOLD: " + String(SHUTDOWN_THRESHOLD) +
    "\n BUF_LEN:            " + String(BUF_LEN) +
    "\n SENSOR_MODE:        " + String(SENSOR_MODE)
  );
}


void Settings::save_mode(String mode_){
  preferences.putString("mode", mode_);
  CONTROLLER_MODE = mode_;
}