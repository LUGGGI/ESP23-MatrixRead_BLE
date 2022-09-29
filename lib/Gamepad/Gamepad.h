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

#define enableX false
#define enableY false
#define enableZ false
#define enableRX false
#define enableRY false
#define enableRZ false
#define enableSlider1 false
#define enableSlider2 false
#define enableRudder false
#define enableThrottle false
#define enableAccelerator true
#define enableBrake true
#define enableSteering true


class Gamepad{
  private:
  BleGamepad gamepad;

  char A = BUTTON_1;
  char B = BUTTON_2;
  char X = BUTTON_3;
  char Y = BUTTON_4;
  char LB = BUTTON_5;
  char RB = BUTTON_6;
  char LT = BUTTON_7;
  char RT = BUTTON_8;
  char Start = BUTTON_9;
  char Back = BUTTON_10;
  char Joy_L = BUTTON_11;
  char Joy_R = BUTTON_12;
  char D_up = BUTTON_13;
  char D_down = BUTTON_14;
  char D_left = BUTTON_15;
  char D_right = BUTTON_16;

  public:

  // setup gamepad
  void setup(String name);

  // update with new sensor values
  void update(uint16_t array_values[6]);
};

#endif /* GAMEPAD_H */