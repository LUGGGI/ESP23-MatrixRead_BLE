#include "Settings.h"


void Settings::preference_setup(){
  preferences.begin("app", false);

  id = preferences.getInt("ID", 0);
  send_freq = preferences.getInt("SEND_FREQ", 50);
  mode = preferences.getString("mode", "BLE_VALUES");
  print_settings();
}

void Settings::setup() {
  Serial.println("Setting up controller... ");
  preference_setup();
  Serial.println("To change controller settings send anything.");
  int time = millis();
  bool set_settings = false;
  while (millis() < time + 5000) {
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
        Serial.print("Setting SEND_FREQ, please enter value to set id to: ");
        while (Serial.available() == 0) {delay(1);} // wait for input
        send_freq = Serial.readString().toInt();
        Serial.println(send_freq);
        preferences.putInt("SEND_FREQ", send_freq);
    } else if (input == "EXIT" ) {
        Serial.println("Exiting Settings");
        set_settings = false;
    }
  }
  
}

void Settings::print_settings(){
  String print_settings = "Controller Settings:";
  print_settings += "\n Data Rate: 115200";
  print_settings += "\n Mode:      ";
  print_settings += mode;
  print_settings += "\n ID:        ";
  print_settings += id;
  print_settings += "\n SEND_FREQ: ";
  print_settings += send_freq;
  Serial.println(print_settings);
}

void Settings::save_mode(String mode_){
  preferences.putString("mode", mode_);
  mode = mode_;
}