/* Settings.h
 * 14.07.2022
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

  // get all settings from flash storage
  void preference_setup();

  // get new value for setting, set it in flash storage and returns value
  int change_setting(String input, String unit="");
  

  public:
  int id = 1; // id of the controller, displayed in name of controller
  int send_freq = 50; // send frequency of new values in ms
  int shutdown_time = 300; // time after the controller turns of in s
  int shutdown_threshold = 400; // read range that has to be exceeded so that the automatic shutdown time resets
  int buf_len = 10; // length of buffer (more increases time for reading sensor)
  String sensor_mode = "Mat"; // sensor for game controller Mat or Ribbon
  // holds the current Mode:
  // BLE_VALUES: Sensor values over Bluetooth low energy
  // SERIAL_BT_VALUES: Sensor values over Serial bus with classic bluetooth
  // GAMEPAD: Sensor values as BLE Gamepad joystick
  String mode = "BLE_VALUES";

  // set up settings and waits for input
  void setup();

  // print settings to serial monitor
  void print_settings();
  
  // updates mode
  void save_mode(String mode_);
};

#endif /* SETTINGS_H */