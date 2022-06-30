/* Settings.h
 * 30.06.2022
 * 
 * Enables to set an read settings
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */
#include <Arduino.h>
#include <Preferences.h>

class Settings {
  private:
  Preferences preferences;
  void preference_setup();
  
  public:

  int id = 0; // id of the controller, displayed in name of controller
  int send_freq = 50; // send frequency of new values in ms
  int auto_shutdown_time = 300; // time after the controller turns of in s
  // holds the current Mode:
  // BLE_VALUES: Sensor values over Bluetooth low energy
  // SERIAL_BT_VALUES: Sensor values over Serial bus with classic bluetooth
  // GAMEPAD: Sensor values as BLE Gamepad joystick
  String mode = "BLE_VALUES";

  void setup();
  void print_settings();
  void save_mode(String mode_);
};