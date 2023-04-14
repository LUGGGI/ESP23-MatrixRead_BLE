#include "Settings.h"


void Settings::setup() {
  Serial.println("Setting up controller... ");
  preferences.begin("app", false);

  ID = preferences.getInt("ID", ID);
  SEND_FREQ = preferences.getInt("SEND_FREQ", SEND_FREQ);
  SHUTDOWN_TIME = preferences.getInt("SHUTDOWN_TIME", SHUTDOWN_TIME);
  SHUTDOWN_THRESHOLD = preferences.getInt("SHUTDOWN_THRESHOLD", SHUTDOWN_THRESHOLD);
  BUF_LEN = preferences.getInt("BUF_LEN", BUF_LEN);
  CONTROLLER_MODE = preferences.getString("mode", CONTROLLER_MODE);
  TOPVAL_MAT =  preferences.getInt("TOPVAL_MAT", TOPVAL_MAT);
  TOPVAL_RIBBON =  preferences.getInt("TOPVAL_RIBBON", TOPVAL_RIBBON);


  print_settings();
  Serial.println("To change controller settings send anything.");


  unsigned long time = millis();
  bool set_settings = false;

  while (set_settings || millis() < time + 2000) {

    if (millis() < time + 2000) { // check for input
      if (Serial.available() > 0) set_settings = true;
      else continue;

    } else {
      print_settings();
      Serial.print("To change a setting (Only settings with only uppercase letters), input the exact name, to exit enter EXIT: ");
      while (Serial.available() == 0) {delay(1);} // wait for input
    }
    
    String input = Serial.readString();
    input.toUpperCase();
    Serial.println(input);
    
    if (input.startsWith("ID")) {
      ID = change_setting(input);

    } else if (input.startsWith("SEND_FREQ")){
      SEND_FREQ = change_setting(input, " in ms");

    } else if (input.startsWith("SHUTDOWN_TIME")){
      SHUTDOWN_TIME = change_setting(input, " in s");

    } else if (input.startsWith("SHUTDOWN_THRESHOLD")){
      SHUTDOWN_THRESHOLD = change_setting(input, " between 0 and 4096");

    } else if (input.startsWith("BUF_LEN")){
      BUF_LEN = change_setting(input);

    } else if (input.startsWith("TOPVAL_MAT")){
      TOPVAL_MAT = change_setting(input);

    } else if (input.startsWith("TOPVAL_RIBBON")){
      TOPVAL_RIBBON = change_setting(input);

    } else if (input.startsWith("EXIT")) {
      Serial.println("Exiting Settings...");
      set_settings = false;

    } else {
      Serial.println("Entered setting not found please try again.");
    }
  }
  print_settings();
}


int Settings::change_setting(String input, String unit, int _value){
  int index = input.indexOf(" ");
  int value;
  if (index != -1) {
    value = input.substring(index+1).toInt();
    input.remove(index);
  } else {
    Serial.print("Setting " + input + unit +", please enter new value: ");
    while (Serial.available() == 0) {delay(1);} // wait for input
    value = Serial.readString().toInt();
    Serial.println(value);
  }
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
    "\n TOPVAL_MAT:         " + String(TOPVAL_MAT) +
    "\n TOPVAL_RIBBON:      " + String(TOPVAL_RIBBON)
  );
}


void Settings::save_mode(String mode_){
  preferences.putString("mode", mode_);
  CONTROLLER_MODE = mode_;
}