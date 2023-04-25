/* Settings.h
 * 24.04.2023
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

  String settings[7][3] = {
    {"ID", "", "0"},
    {"SEND_FREQ", " in ms ", "50"},
    {"OFF_TIME", " in s ", "300"},
    {"OFF_THRESHOLD", " max 4096", "400"},
    {"BUF_LEN", "", "10"},
    {"TOPVAL_MAT", " max 4096", "3100"},
    {"TOPVAL_RIBBON", " max 4096", "3300"}
  };
  

  public:
  String CONTROLLER_MODE = "BLE_VALUES"; // holds the current Mode: BLE_VALUES, SERIAL_BT_VALUES, GAMEPAD
  int ID = settings[0][2].toInt(); // id of the controller, displayed in name of controller
  int SEND_FREQ = settings[1][2].toInt(); // send frequency of new values in ms
  int OFF_TIME = settings[2][2].toInt(); // time after the controller turns of in s
  int OFF_THRESHOLD = settings[3][2].toInt(); // read range that has to be exceeded so that the automatic shutdown time resets
  int BUF_LEN = settings[4][2].toInt(); // length of buffer (more increases time for reading sensor)
  int TOPVAL_MAT = settings[5][2].toInt(); // threshold for mat to detect jump
  int TOPVAL_RIBBON = settings[6][2].toInt(); // max value fro ribbon
  

  // set up settings and waits for input
  void setup();

  // read values form memory into variables
  void read_from_memory();

  // resets all settings to default value (given in settings array)
  void change_settings_to_default();

  // print settings to serial monitor
  void print_settings();
  
  // updates mode
  void save_mode(String mode_);
};

#endif /* SETTINGS_H */