#include "Gamepad.h"


void Gamepad::setup(String name, uint16_t output_array[6]){
  gamepad = BleGamepad(name.c_str(), "DITF", 100);

  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setAxesMin(0x8001); // -32767
  bleGamepadConfig.setAxesMax(0x7FFF); // 32767

  Serial.print("MinVal: ");
  for(int i=0; i<6; ++i){
    minVal[i] = output_array[i] - 300;
    if (minVal[i] > 4096) minVal[i] = 0;
    Serial.print(String(minVal[i]) + " ");
  }
  Serial.println();
  
  gamepad.begin(&bleGamepadConfig);
}


void Gamepad::update(uint16_t array_values[6]){
  if(gamepad.isConnected() || true){
    int left_right = array_values[0] - array_values[1];
    
    if (left_right < -minVal[1]) left_right = -minVal[1];
    else if (left_right > minVal[0]) left_right = minVal[0];
    JoyL_X = map(left_right, -minVal[1], minVal[0], -32767, 32767);


    char print_buffer[60];
    sprintf(print_buffer, " Left:%4u, Right:%4u, Direction:%4d, Mapped: %5d ", 
      array_values[1], array_values[0], left_right, JoyL_X
    );
    Serial.print(print_buffer);   
    
    
    gamepad.setAxes(JoyL_X, JoyL_Y, JoyR_X, 0, JoyR_Y, 0, 0, 0);

    // Nitro
    if (detect_jump(array_values[1], array_values[0], minVal[1], minVal[0], 'B')) {
      gamepad.press(B);
      delay(5);
      gamepad.release(B);
    }
    // Gas
    if (detect_jump(array_values[1], array_values[0], minVal[1], minVal[0], 'L')) {
      toggle_button(Y);
    }

    // Reset
    if (detect_jump(array_values[1], array_values[0], minVal[1], minVal[0], 'R')) {
      gamepad.press(LB);
      delay(5);
      gamepad.release(LB);
    }
  }
}

bool Gamepad::detect_jump(uint16_t left, uint16_t right, uint16_t left_min, uint16_t right_min, char which){

  if (left < left_min + 300 && right < right_min + 300) {
    jump_start_time = millis();
  } else if (jump_start_time != 0) {
    if (which == 'B' && left > topVal && right > topVal){
      jump_start_time = 0;
      Serial.print(" -> Jump!!! ");
      return true;
    } else if (which == 'L' && left > topVal && right < right_min + 300 && millis() > jump_start_time + 100) {
      jump_start_time = 0;
      Serial.print(" -> Jump Left!!! ");
      return true;
    } else if (which == 'R' && right > topVal && left < left_min + 300 && millis() > jump_start_time + 100) {
      jump_start_time = 0;
      Serial.print(" -> Jump Right!!! ");
      return true;
    }
  }

  if (millis() > jump_start_time + 2000) {
    jump_start_time = 0;
  }

  return false;
}

void Gamepad::toggle_button(char button){
  if (gamepad.isPressed(button)) gamepad.release(button);
  else gamepad.press(button);
}