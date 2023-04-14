#include "Gamepad.h"

#define SIZE(n) sizeof(n) / sizeof(n[0]) // get length of array

void Gamepad::setup(String name, MatrixRead matrix, uint16_t _topValM, uint16_t _topValR){
  BleGamepadConfiguration bleGamepadConfig;
  topValM = _topValM;
  topValR = _topValR;

  matrix.get_values();
  Output out = matrix.get_output();

  if (out.output_array[0] == 0 && out.output_array[2] == 0 && out.output_array[4] == 0
   || out.output_array[1] == 0 && out.output_array[3] == 0 && out.output_array[5] == 0) {
    SensorMode = "Ribbon";
  }
  bleGamepadConfig.setAxesMin(0x8001); // -32767
  bleGamepadConfig.setAxesMax(0x7FFF); // 32767

  Serial.print("Mode: " + SensorMode + ", ");
  Serial.print("MinVal: ");
  for(int i=0; i<SIZE(minVal) && SIZE(out.output_array); ++i){
    minVal[i] = out.output_array[i] - minVal_offset;
    if (minVal[i] > 4096) minVal[i] = 0;
    Serial.print(String(minVal[i]) + " ");
  }
  Serial.println();
  name += SensorMode;
  gamepad = BleGamepad(name.c_str(), "DITF", 100);
  gamepad.begin(&bleGamepadConfig);
}


void Gamepad::update(uint16_t array_values[6]){

  // For Ribbon 
  if(gamepad.isConnected() && SensorMode == "Ribbon"){
    // acceleration
    // int16_t accel = minVal[1] - array_values[1];
    // if (accel < 0) accel = 0;
    // else if (accel > minVal[1]-topValR) accel = minVal[1]-topValR;
    // JoyR_Y = map(accel, 0, minVal[1]-topValR, 0, 32767);

    // deceleration
    int16_t accel = array_values[1];
    if (accel < topValR) accel = topValR;
    else if (accel > minVal[1]) accel = minVal[1];
    JoyR_Y = map(accel, topValR, minVal[1], -32767, 32767);

    char print_buffer[60];
    sprintf(print_buffer, " Accel:%4d, Mapped:%5d ", accel, JoyR_Y);
    Serial.print(print_buffer);

    gamepad.setAxes(JoyL_X, JoyL_Y, JoyR_X, 0, JoyR_Y, 0, 0, 0);
  }

  // For mat
  if(gamepad.isConnected() && SensorMode == "Mat"){
    int16_t left_right = array_values[0] - array_values[1];
    
    // Fxi for integer overflow
    if (left_right < -minVal[1]) left_right = -minVal[1];
    else if (left_right > minVal[0]) left_right = minVal[0];
    
    JoyL_X = map(left_right, -minVal[1], minVal[0], -32767, 32767);

    if (abs(left_right) < left_right_dead_zone) JoyL_X = 0;

    
    detect_jump(array_values[1], array_values[0], minVal[1], minVal[0]);
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

    if (millis() <= jump_dead_zone_start + jump_dead_zone) JoyL_X = 0; 
    else if (jump_dead_zone_start != 0) jump_dead_zone_start = 0;

    char print_buffer[100];
    sprintf(print_buffer, " Left:%4u, Right:%4u, Direction:%5d, Mapped:%6d | Accel:%5d,  %s", 
      array_values[1], array_values[0], left_right, JoyL_X, JoyR_Y, jump.c_str()
    );
    Serial.print(print_buffer);  

    gamepad.setAxes(JoyL_X, JoyL_Y, JoyR_X, 0, JoyR_Y, 0, 0, 0);
  }
}

bool Gamepad::detect_jump(uint16_t left, uint16_t right, uint16_t left_min, uint16_t right_min){
  jump = "";
  if (!unpressed && left < (left_min + 2*minVal_offset) && right < (right_min + 2*minVal_offset)) {
    unpressed = true;
    jump_dead_zone_start = millis();
  } else if (unpressed) {
    // check for landing on both feet
    if (left > topValM && right > topValM){
      jump = " -> Jump ";
      // check for landing on left foot
    } else if (left > topValM && right < right_min + 2*minVal_offset) {
      if (millis() > jump_one_delay_start + 100){
        jump = " -> Jump Left ";
      } else if (jump_one_delay_start == 0) jump_one_delay_start = millis();
      // check for landing on right foot
    } else if (right > topValM && left < left_min + 2*minVal_offset) {
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