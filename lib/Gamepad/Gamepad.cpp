#include "Gamepad.h"
#include "math.h"

void Gamepad::setup(String name){
  gamepad = BleGamepad(name.c_str(), "DITF", 100);
  gamepad.begin();
}

void Gamepad::update(uint16_t array_values[6]){
  if(gamepad.isConnected()){
    Serial.print("Left: ");
    Serial.print(array_values[2]);
    Serial.print(" Right: ");
    Serial.print(array_values[4]);
    int left_right = array_values[4] - array_values[2];
    Serial.print(" Direction: ");
    Serial.print(left_right);

    left_right = map(left_right, -4095, 4095, -32767, 32767);
    Serial.print(" maped: ");
    Serial.println(left_right);

    gamepad.setAxes(left_right, 0, 0, 0, 0, 0, 0, 0);
  }
}