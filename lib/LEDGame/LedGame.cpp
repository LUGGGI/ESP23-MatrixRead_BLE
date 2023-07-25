#include "LedGame.h"

#define SIZE(n) sizeof(n) / sizeof(n[0]) // get length of array

void LedGame::setup(MatrixRead matrix, uint16_t _topValM){
  for (int i=0; i<GAME_FIELD_SIZE; ++i) {
    field[i] = FIELD_COLOR;
  }
  // read sensor one time
  matrix.get_values();
  Output out = matrix.get_output();

  // save min_value
  Serial.print("Min value: ");
  for(int i=0; i<SIZE(out.output_array); ++i){
    min_value[i] = out.output_array[i];
    Serial.print(String(min_value[i]) + " ");
  }
  right_max = topVal - min_value[0];
  left_max = topVal - min_value[1];
  Serial.println();
}

void LedGame::update(uint16_t array_values[6]) {
  // normalize values to the min values 
  int16_t right = array_values[0]-min_value[0];
  if (right < 0 ) right = 0;
  int16_t left = array_values[1]-min_value[1];
  if (left < 0) left = 0;

  int16_t ratio_left_right = right - left;

  // account for overflow
  if (ratio_left_right < -topVal) {
    ratio_left_right = -topVal;
  } else if  (ratio_left_right > topVal) {
    ratio_left_right = topVal;
  }
  // get position in game field
  player_position = map(ratio_left_right, -topVal, topVal, 0, GAME_FIELD_SIZE-PLAYER_SIZE);

  // if over target start timer
  if (target_time == 0 && (player_position < target && player_position+PLAYER_SIZE > target)) {
    target_color = '*';
    target_time = millis();
  }

  // if timer > TARGET_TIME and player still over target -> WIN
  else if (millis() > TARGET_TIME+target_time && (player_position < target && player_position+PLAYER_SIZE > target)) {
    Serial.println("\n WIN \n");
    delay(1000);
    target_time = 0;
    target = random(PLAYER_SIZE + 5, GAME_FIELD_SIZE-PLAYER_SIZE-5);
  } 

  // if player not over target reset timer
  else if (target < player_position || target > player_position+PLAYER_SIZE) {
    target_time = 0;
  }

  display();
}

void LedGame::display() {
  // reset field
  for (int i=0; i<GAME_FIELD_SIZE; ++i) {
    field[i] = FIELD_COLOR;
  }

  // add player
  for (int i=0; i<PLAYER_SIZE; ++i) {
    field[player_position + i] = PLAYER_COLOR;
  }
  // add target
  field[target] = target_color;

  // display field
  for (int i=0; i<GAME_FIELD_SIZE; ++i) {
    Serial.print(field[i]);
  }
  int time = 0;
  if (target_time != 0) {
    time = millis() - target_time;
  }
  Serial.print("  , " + String(player_position) + ", " + String(target) + ", " + String(time));
}
