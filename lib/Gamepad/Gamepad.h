/* Gamepad.h
 * 23.06.2022
 * 
 * Allows the controller to function as a ble gamepad
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */

#include <BleGamepad.h>
#include <Arduino.h>
#include <stdint.h>


class Gamepad{
  private:
  BleGamepad gamepad;
  public:

  // setup gamepad
  void setup();

  // update with new sensor values
  void update(uint16_t array_values[6]);
};