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

  // get new value for setting, set it in flash storage and returns value
  int change_setting(String input, String unit="");
  

  public:
  int ID = 1; // id of the controller, displayed in name of controller
  int SEND_FREQ = 50; // send frequency of new values in ms
  int SHUTDOWN_TIME = 300; // time after the controller turns of in s
  int SHUTDOWN_THRESHOLD = 400; // read range that has to be exceeded so that the automatic shutdown time resets
  int BUF_LEN = 10; // length of buffer (more increases time for reading sensor)
  String SENSOR_MODE = "Mat"; // sensor for game controller Mat or Ribbon
  String CONTROLLER_MODE = "BLE_VALUES"; // holds the current Mode: BLE_VALUES, SERIAL_BT_VALUES, GAMEPAD

  // set up settings and waits for input
  void setup();

  // print settings to serial monitor
  void print_settings();
  
  // updates mode
  void save_mode(String mode_);
};

#endif /* SETTINGS_H */