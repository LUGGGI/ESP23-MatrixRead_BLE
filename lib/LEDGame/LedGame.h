/* LedGame.h
 * 20.06.2023
 * 
 * Controls LED game
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */
#ifndef LED_GAME_H
#define LED_GAME_H

#include <Arduino.h>
#include "MatrixRead.h"

#define GAME_FIELD_SIZE 200
#define PLAYER_SIZE 10

#define FIELD_COLOR 'o'
#define TARGET_COLOR 'X'
#define PLAYER_COLOR '|'

#define TARGET_TIME 2000 //ms

class LedGame{
  private:
  char field[GAME_FIELD_SIZE];

  int target = 100;
  char target_color = TARGET_COLOR;
  int player_position = 100;
  int target_time = 0;

  uint16_t topVal = 2000; // max value for mat
  uint16_t min_value[6] = {0}; // sensor value without pressing (baseline)
  int16_t right_max = 0; // max value for the right pad
  int16_t left_max = 0; // max value for the left pad

  public:
  // setup led game
  void setup(MatrixRead matrix, uint16_t _topValM);

  void update(uint16_t array_values[6]);

  void display();
};

#endif /* LED_GAME_H */