/* Settings.h
 * 19.10.2022
 * 
 * Enables to set an read settings
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */
#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>

class Settings {
  private:
  Preferences preferences;

  String settings[7][2] = {
    {"ID", ""},
    {"SEND_FREQ", " in ms "},
    {"OFF_TIME", " in s "},
    {"OFF_THRESHOLD", " max 4096"},
    {"BUF_LEN", ""},
    {"TOPVAL_MAT", " max 4096"},
    {"TOPVAL_RIBBON", " max 4096"}
  };
  

  public:
  int ID = 0; // id of the controller, displayed in name of controller
  int SEND_FREQ = 50; // send frequency of new values in ms
  int OFF_TIME = 300; // time after the controller turns of in s
  int OFF_THRESHOLD = 400; // read range that has to be exceeded so that the automatic shutdown time resets
  int BUF_LEN = 10; // length of buffer (more increases time for reading sensor)
  int TOPVAL_MAT = 3100;
  int TOPVAL_RIBBON = 3300;
  String CONTROLLER_MODE = "BLE_VALUES"; // holds the current Mode: BLE_VALUES, SERIAL_BT_VALUES, GAMEPAD

  // set up settings and waits for input
  void setup();

  // read values form memory into variables
  void update_variables();

  // print settings to serial monitor
  void print_settings();
  
  // updates mode
  void save_mode(String mode_);
};

#endif /* SETTINGS_H */