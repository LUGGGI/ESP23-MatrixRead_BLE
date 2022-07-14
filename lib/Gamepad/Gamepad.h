/* Gamepad.h
 * 14.07.2022
 * 
 * Allows the controller to function as a ble gamepad
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */
#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Arduino.h>
#include <BleGamepad.h>


class Gamepad{
  private:
  BleGamepad gamepad;
  public:

  // setup gamepad
  void setup(String name);

  // update with new sensor values
  void update(uint16_t array_values[6]);
};

#endif /* GAMEPAD_H */