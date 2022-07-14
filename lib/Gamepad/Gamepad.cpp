#include "Gamepad.h"


void Gamepad::setup(String name){
  gamepad = BleGamepad(name.c_str(), "DITF", 100);
  gamepad.begin();
}


void Gamepad::update(uint16_t array_values[6]){
  if(gamepad.isConnected()){
    int left_right = array_values[4] - array_values[2];
    int left_right_mapped = map(left_right, -4095, 4095, -32767, 32767);
    
    Serial.print(
      "Left: " + String(array_values[2]) + 
      " Right: " + String(array_values[4]) + 
      " Direction: " + String(left_right) + 
      " maped: " + String(left_right_mapped)
    );

    gamepad.setAxes(left_right, 0, 0, 0, 0, 0, 0, 0);
  }
}