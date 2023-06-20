/* LedGame.h
 * 19.10.2022
 * 
 * Allows the controller to function as a ble gamepad
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */
#ifndef LED_GAME_H
#define LED_GAME_H

#include <Arduino.h>
#include "MatrixRead.h"

#define NUM_GAME_FIELD 200
#define PLAYER_SIZE 5

class LedGame{
  private:
  char field[NUM_GAME_FIELD] = {'0'};

  int target = 100;
  int player[PLAYER_SIZE] = {40, 41, 42, 43, 44};

  public:
  // setup led game
  void setup();

  void update();
};

#endif /* LED_GAME_H */