#include "Gamepad.h"


void Gamepad::setup(String name){
  gamepad = BleGamepad(name.c_str(), "DITF", 100);

  BleGamepadConfiguration bleGamepadConfig;
  // bleGamepadConfig.setWhichAxes(enableX, enableY, enableZ, enableRX, enableRY, enableRZ, enableSlider1, enableSlider2);      // Can also be done per-axis individually. All are true by default
  bleGamepadConfig.setAxesMin(0x8001); // -32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
  bleGamepadConfig.setAxesMax(0x7FFF); // 32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal 
  gamepad.begin(&bleGamepadConfig);
}


void Gamepad::update(uint16_t array_values[6]){
  if(gamepad.isConnected()){
    // int left_right = array_values[4] - array_values[2];
    // int left_right_mapped = map(left_right, -4095, 4095, -32767, 32767);
    
    // Serial.print(
    //   "Left: " + String(array_values[2]) + 
    //   " Right: " + String(array_values[4]) + 
    //   " Direction: " + String(left_right) + 
    //   " maped: " + String(left_right_mapped)
    // );

    // gamepad.setAxes(left_right, 0, 0, 0, 0, 0, 0, 0);

    Serial.println("BUTTON_1");
    gamepad.press(A);
    delay(500);
    gamepad.release(A);
    delay(500);
    Serial.println("BUTTON_1");
    gamepad.press(BUTTON_1);
    delay(500);
    gamepad.release(BUTTON_1);
    delay(500);
    
    gamepad.setAxes(32767, 32767, 32767, 0, 32767, 0, 0, 0);
    delay(500);
    gamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);
    delay(500);

    gamepad.setAxes(32767, 32767, 32767, 0, 0, 0, 0, 0);
    delay(500);
    gamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);
    delay(500);

    gamepad.setAxes(32767, 32767, 0, 32767, 0, 0, 0, 0);
    delay(500);
    gamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);
    delay(500);

    gamepad.setAxes(32767, 32767, 0, 0, 32767, 0, 0, 0);
    delay(500);
    gamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);
    delay(500);

    gamepad.setAxes(32767, 32767, 0, 0, 0, 32767, 0, 0);
    delay(500);
    gamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);
    delay(500);

    gamepad.setAxes(32767, 32767, 0, 0, 0, 0, 32767, 0);
    delay(500);
    gamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);
    delay(500);

    gamepad.setAxes(32767, 32767, 0, 0, 0, 0, 0, 32767);
    delay(500);
    gamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);
    delay(500);

    // for(int i=0; i<32767; i+=1000){
    //   gamepad.setLeftThumb(i, 0);
    //   delay(50);
    // }
    // delay(500);
    // gamepad.setLeftThumb(0, 0);

    // for(int i=0; i<32767; i+=1000){
    //   gamepad.setLeftThumb(0, i);
    //   delay(50);
    // }
    // delay(500);
    // gamepad.setLeftThumb(0, 0);

    // for(int i=0; i<32767; i+=1000){
    //   gamepad.setLeftThumb(i, i);
    //   delay(50);
    // }
    // delay(500);
    // gamepad.setLeftThumb(0, 0);

    

    // for(int i=0; i<32767; i+=1000){
    //   gamepad.setLeftTrigger(i);
    //   delay(50);
    // }
    // delay(500);
    // gamepad.setLeftTrigger(0);
    // for(int i=0; i<32767; i+=1000){
    //   gamepad.setRightTrigger(i);
    //   delay(50);
    // }
    // delay(500);
    // gamepad.setRightTrigger(0);

    // for(int i=0; i<32767; i+=1000){
    //   gamepad.setSlider1(i);
    //   delay(50);
    // }
    // delay(500);
    // gamepad.setSlider1(0);
  }
}