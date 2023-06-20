#include "LedGame.h"

#define SIZE(n) sizeof(n) / sizeof(n[0]) // get length of array

void LedGame::setup(){
  for (int i=0; i<SIZE(field); ++i) {
    field[i] = 'o';
  }
  Serial.println("\n\n");
  update();
  Serial.println("\n\n");
}

void LedGame::update() {

  // add player
  for (int i=0; i<SIZE(player); ++i) {
    field[player[i]] = '|';
  }
  // add target
  field[target] = '+';

  // display field
  for (int i=0; i<SIZE(field); ++i) {
    Serial.print(field[i]);
  }
}


