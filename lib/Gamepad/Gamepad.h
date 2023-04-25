/* Gamepad.h
 * 19.10.2022
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
#include "MatrixRead.h"


class Gamepad{
  private:
  uint16_t topValM; // max value for mat
  uint16_t topValR; // switching threshold ribbon
  const int jump_time_dead_zone = 500; // time in ms after jump with no detection
  const int jump_topVal_offset = 500;
  const int16_t left_right_dead_zone = 150;
  const uint16_t min_value_margin = 300; // value added/subtracted from min_value to have better margin

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

  uint16_t min_value[6] = {0}; // sensor value without pressing (baseline)
  int16_t right_max = 0; // max value for the right pad
  int16_t left_max = 0; // max value for the left pad
  bool unpressed = false;
  String jump = "";
  unsigned long jump_one_delay_start = 0;
  unsigned long jump_dead_zone_start = 0;

  public:
  // setup gamepad
  void setup(String name, MatrixRead matrix, uint16_t _topValM, uint16_t topValR);

  // update with new sensor values
  void update(uint16_t array_values[6]);

  // detect jump which: L: left, R: right, B: both 
  bool detect_jump(uint16_t left, uint16_t right, uint16_t left_min, uint16_t right_min);

  void toggle_button(char button);
};

#endif /* GAMEPAD_H */