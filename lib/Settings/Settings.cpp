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
        Serial.print("Setting ID, please enter value to set id to: ");
        while (Serial.available() == 0) {delay(1);} // wait for input
        id = Serial.readString().toInt();
        Serial.println(id);
        preferences.putInt("ID", id);

    } else if (input =="SEND_FREQ"){
        Serial.print("Setting SEND_FREQ in ms, please enter value to set id to: ");
        while (Serial.available() == 0) {delay(1);} // wait for input
        send_freq = Serial.readString().toInt();
        Serial.println(send_freq);
        preferences.putInt("AUTO_SHUTDOWN_TIME", send_freq);

    } else if (input =="SHUTDOWN_TIME"){
        Serial.print("Setting SHUTDOWN_TIME in s, please enter value to set id to: ");
        while (Serial.available() == 0) {delay(1);} // wait for input
        shutdown_time = Serial.readString().toInt();
        Serial.println(shutdown_time);
        preferences.putInt("SHUTDOWN_TIME", shutdown_time);

    } else if (input =="SHUTDOWN_THRESHOLD"){
        Serial.print("Setting SHUTDOWN_THRESHOLD, please enter value to set id to: ");
        while (Serial.available() == 0) {delay(1);} // wait for input
        shutdown_threshold = Serial.readString().toInt();
        Serial.println(shutdown_threshold);
        preferences.putInt("SHUTDOWN_THRESHOLD", shutdown_threshold);

    } else if (input =="BUF_LEN"){
        Serial.print("Setting BUF_LEN, please enter value to set id to: ");
        while (Serial.available() == 0) {delay(1);} // wait for input
        buf_len = Serial.readString().toInt();
        Serial.println(buf_len);
        preferences.putInt("BUF_LEN", buf_len);

    } else if (input == "EXIT" ) {
        Serial.println("Exiting Settings");
        set_settings = false;
    } else {
      Serial.println("Entered setting not found please try again.");
    }
  }
}

void Settings::print_settings(){
  Serial.println("Controller Settings: \n Data Rate: 115200 \n Mode:      " + String(mode) + "\n ID: " + String(id) + "\n SEND_FREQ: " + String(send_freq) + "\n SHUTDOWN_TIME: " + String(shutdown_time) + "\n SHUTDOWN_THRESHOLD: " + String(shutdown_threshold));
}

void Settings::save_mode(String mode_){
  preferences.putString("mode", mode_);
  mode = mode_;
}