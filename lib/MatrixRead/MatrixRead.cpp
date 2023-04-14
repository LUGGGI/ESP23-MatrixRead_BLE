#include "MatrixRead.h"

#define SIZE(n) sizeof(n) / sizeof(n[0]) // get length of array

void MatrixRead::setup(int _SHUTDOWN_TIME, int _SHUTDOWN_THRESHOLD, int _BUF_LEN){
  SHUTDOWN_TIME = _SHUTDOWN_TIME * 1000;
  SHUTDOWN_THRESHOLD = _SHUTDOWN_THRESHOLD;
  BUF_LEN = _BUF_LEN;
  pinMode(A_PIN_ORANGE, INPUT);
  pinMode(A_PIN_BROWN, INPUT);

  for (int i=0; i<SIZE(D_PINS); ++i){
    pinMode(D_PINS[i], INPUT);
  }
}


void MatrixRead::read(short row, short col){
  if (col == 0){
    buffer[row][col] += analogRead(A_PIN_BROWN);
  }
  else if (col ==1){
    buffer[row][col] += analogRead(A_PIN_ORANGE);
  }
  else exit(1); // should not happen
}


void MatrixRead::get_values(void){
  out.run_time = millis();

  // set array to zero
  for(int i=0; i<COLS; ++i){
    for(int j=0; j<ROWS; ++j){
      buffer[i][j] = 0;
    }
  }

  // read values BUF_LEN times into array
  for (int i=0; i<COLS; ++i) {
    pinMode(D_PINS[i], OUTPUT);
    digitalWrite(D_PINS[i], HIGH);
    delay(4);
    for(int j=0; j<BUF_LEN; ++j) {
      for(int k=0; k<ROWS; ++k) {
        read(i, k);
      }
    }
    digitalWrite(D_PINS[i], LOW);
    pinMode(D_PINS[i], INPUT);
  }
}


Output MatrixRead::get_output(void){
  bool over_threshold = false;
  // fill output array
  for(int i=0; i<COLS; ++i){
    for(int j=0; j<ROWS; ++j){
      buffer[i][j] = round(buffer[i][j]/ (float) BUF_LEN);
      out.output_array[i*ROWS+j] = (uint16_t) buffer[i][j];

      // check if activity is detected (values leave the SHUTDOWN_THRESHOLD range)
      if (abs((uint16_t) (buffer[i][j] - last_activity_value[i][j])) > SHUTDOWN_THRESHOLD){
        last_activity_value[i][j] = buffer[i][j];
        over_threshold = true;
      }
    }
  }

  // requests for shutdown if SHUTDOWN_TIME is exceeded
  if (over_threshold){
    last_activity_time = millis();
    shutdown_requested = false;
  } else if (millis() > (last_activity_time + SHUTDOWN_TIME)) {
    shutdown_requested = true;
    return out;
  }

  // csv output
  out.csv_values = "";
  for(int i=0; i<COLS; ++i){
    for(int j=0; j<ROWS; ++j){ 
      out.csv_values += String(buffer[i][j]) + ", ";
    }
  }

  // formatted output
  out.format_values = ""; //resets the output string
  for(int i=0; i<COLS; ++i){
    for(int j=0; j<ROWS; ++j){
      char value[5];
      sprintf(value, "%4u", buffer[i][j]);
      out.format_values += " " + String(i+1) + "-" + String(j+1) + ":" + String(value);
    }
  }
  // Allows for a nicer display in Arduino IDE plotter
  out.format_values += " 0 4096  ";

  // Seconds until shutdown resets if activity is detected
  // out.format_values += (last_activity_time + SHUTDOWN_TIME - millis()) / 1000;

  return out;
}