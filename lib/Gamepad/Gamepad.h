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

  String SensorMode = "Mat"; //"Ribbon"

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

  int16_t JoyL_X = 0;
  int16_t JoyL_Y = 0;

  int16_t JoyR_X = 0;
  int16_t JoyR_Y = 0;

  uint16_t minVal[6] = {0};
  uint16_t topValM = 3900;
  uint16_t topValR = 2800;

  unsigned long jump_start_time = 0;


  public:

  // setup gamepad
  void setup(String name, String sensor_mode, uint16_t output_array[6]);

  // update with new sensor values
  void update(uint16_t array_values[6]);

  // detect jump which: L: left, R: right, B: both 
  bool detect_jump(uint16_t left, uint16_t right, uint16_t left_min, uint16_t right_min, char which);

  void toggle_button(char button);
};

#endif /* GAMEPAD_H */