#include "Gamepad.h"

#define SIZE(n) sizeof(n) / sizeof(n[0]) // get length of array

void Gamepad::setup(String name, MatrixRead matrix, uint16_t _topValM, uint16_t _topValR){
  BleGamepadConfiguration bleGamepadConfig;
  topValM = _topValM;
  topValR = _topValR;

  bleGamepadConfig.setAxesMin(0x8001); // -32767
  bleGamepadConfig.setAxesMax(0x7FFF); // 32767

  // read sensor one time
  matrix.get_values();
  Output out = matrix.get_output();

  // switch to Ribbon if a ribbon is connected
  if (out.output_array[0] == 0 && out.output_array[2] == 0 && out.output_array[4] == 0
   || out.output_array[1] == 0 && out.output_array[3] == 0 && out.output_array[5] == 0) {
    SensorMode = "Ribbon";
  }
  Serial.print("Mode: " + SensorMode + ", ");

  // save min_value
  Serial.print("Min value: ");
  for(int i=0; i<SIZE(out.output_array); ++i){
    min_value[i] = out.output_array[i];
    Serial.print(String(min_value[i]) + " ");
  }
  right_max = topValM - min_value[0];
  left_max = topValM - min_value[1];
  Serial.println();

  // create BLE gamepad
  name += SensorMode;
  gamepad = BleGamepad(name.c_str(), "DITF", 100);
  gamepad.begin(&bleGamepadConfig);
}


void Gamepad::update(uint16_t array_values[6]){

  // For Ribbon 
  if(gamepad.isConnected() && SensorMode == "Ribbon"){
    // acceleration
    // int16_t accel = min_value[1] - array_values[1];
    // if (accel < 0) accel = 0;
    // else if (accel > min_value[1]-topValR) accel = min_value[1]-topValR;
    // JoyR_Y = map(accel, 0, min_value[1]-topValR, 0, 32767);

    // deceleration
    int16_t accel = array_values[1];
    if (accel < topValR) accel = topValR;
    else if (accel > min_value[1] - min_value_margin) accel = min_value[1] - min_value_margin;
    JoyR_Y = map(accel, topValR, min_value[1], -32767, 32767);

    char print_buffer[60];
    sprintf(print_buffer, " Accel:%4d, Mapped:%5d ", accel, JoyR_Y);
    Serial.print(print_buffer);

    gamepad.setAxes(JoyL_X, JoyL_Y, JoyR_X, 0, JoyR_Y, 0, 0, 0);
  }

  // For mat
  if(gamepad.isConnected() && SensorMode == "Mat"){
    // normalize values to the min values 
    int16_t right = array_values[0]-min_value[0];
    if (right < 0 ) right = 0;
    int16_t left = array_values[1]-min_value[1];
    if (left < 0) left = 0;

    int16_t ratio_left_right = right - left;

    // dead zone
    if (abs(ratio_left_right) < left_right_dead_zone) JoyL_X = 0;
    // steer to the right
    else if (ratio_left_right >= 0) {
      if (ratio_left_right > right_max) ratio_left_right = right_max;
      JoyL_X = map(ratio_left_right, left_right_dead_zone, right_max, 0, 32767);
    }
    // steer to the left
    else if (ratio_left_right < 0) {
      if (ratio_left_right < -left_max) ratio_left_right = -left_max;
      JoyL_X = map(ratio_left_right, -left_right_dead_zone, -left_max, 0, -32767);
    }

    
    detect_jump(array_values[1], array_values[0], min_value[1], min_value[0]);
    // Nitro
    if (gamepad.isPressed(B)) gamepad.release(B);
    if (jump == " -> Jump ") {
      gamepad.press(B);
    }
    // Accelerate
    if (jump == " -> Jump Left ") {
      if (JoyR_Y == 32767) JoyR_Y = 0;
      else JoyR_Y = 32767;
    }
    // Reset
    if (gamepad.isPressed(LB)) gamepad.release(LB);
    if (jump == " -> Jump Right ") {
      gamepad.press(LB);
    }

    if (millis() <= jump_dead_zone_start + jump_time_dead_zone) JoyL_X = 0; 
    else if (jump_dead_zone_start != 0) jump_dead_zone_start = 0;

    char print_buffer[100];
    sprintf(print_buffer, " Left:%4u, Right:%4u, Direction:%5d, Mapped:%6d | Accel:%5d,  %s", 
      left, right, ratio_left_right, JoyL_X, JoyR_Y, jump.c_str()
    );
    Serial.print(print_buffer);  

    gamepad.setAxes(JoyL_X, JoyL_Y, JoyR_X, 0, JoyR_Y, 0, 0, 0);
  }
}

bool Gamepad::detect_jump(uint16_t left, uint16_t right, uint16_t left_min, uint16_t right_min){
  jump = "";
  // check if mat is unpressed
  if (!unpressed && left < (left_min + min_value_margin) && right < (right_min + min_value_margin)) {
    unpressed = true;
    jump_dead_zone_start = millis();
  } else if (unpressed) {
    // check for landing on both feet
    if (left > topValM-jump_topVal_offset && right > topValM-jump_topVal_offset){
      jump = " -> Jump ";
      // check for landing on left foot
    } else if (left > topValM-jump_topVal_offset && right < right_min + min_value_margin) {
      if (millis() > jump_one_delay_start + 100){
        jump = " -> Jump Left ";
      } else if (jump_one_delay_start == 0) jump_one_delay_start = millis();
      // check for landing on right foot
    } else if (right > topValM-jump_topVal_offset && left < left_min + min_value_margin) {
      if (millis() > jump_one_delay_start + 100){
        jump = " -> Jump Right ";
      } else if (jump_one_delay_start == 0) jump_one_delay_start = millis();

    }
  }
  if (jump != "") {
    jump_dead_zone_start = millis();
    unpressed = false;
    jump_one_delay_start = 0;
    return true;
  }
  if (millis() > jump_one_delay_start + 2000) jump_one_delay_start = 0;
  return false;
}

void Gamepad::toggle_button(char button){
  if (gamepad.isPressed(button)) gamepad.release(button);
  else gamepad.press(button);
}