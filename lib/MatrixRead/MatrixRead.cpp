#include "MatrixRead.h"

#include <math.h>

void MatrixRead::setup(int shutdown_time, int shutdown_threshold, int buf_len){
  SHUTDOWN_TIME = shutdown_time * 1000;
  SHUTDOWN_THRESHOLD = shutdown_threshold;
  BUF_LEN = buf_len;
  pinMode(APIN_ORANGE, INPUT);
  pinMode(APIN_BROWN, INPUT);

  for (int i=0; i<3; ++i){
    pinMode(DPINS[i], INPUT);
  }
}

void MatrixRead::read(short row, short col){
  if (col == 0){
    x[row][col] += analogRead(APIN_BROWN);
  }
  else if (col ==1){
    x[row][col] += analogRead(APIN_ORANGE);
  }
  else exit(0);
}

void MatrixRead::get_values(void){
  out.run_time = millis();

  // set array to zero
  for(int i=0; i<3; ++i){
    for(int j=0; j<2; ++j){
      x[i][j] = 0;
    }
  }
  for (int i=0; i<3; ++i){
    pinMode(DPINS[i], OUTPUT);
    digitalWrite(DPINS[i], HIGH);
    delay(4);
    for(int i=0; i<BUF_LEN; ++i){
      read(0, 0);
      read(0, 1);
    }
    digitalWrite(DPINS[i], LOW);
    pinMode(DPINS[i], INPUT);
  }
}

Output MatrixRead::get_output(void){
  bool over_threshold = false;
  // fill array
  for(int i=0; i<3; ++i){
    for(int j=0; j<2; ++j){
      x[i][j] = (uint16_t) lround(x[i][j] / BUF_LEN);
      
      if (abs(x[i][j] - last_activity_value[i][j]) > SHUTDOWN_THRESHOLD){
        last_activity_value[i][j] = x[i][j];
        over_threshold = true;
      }
      out.array_values[i*2+j] = x[i][j];
    }
  }

  if (over_threshold){
    last_activity_time = millis();
    shutdown_requested = false;
  }
  if (millis() > (last_activity_time + SHUTDOWN_TIME)) {
    shutdown_requested = true;
    return out;
  }

  // csv output
  out.csv_values = "";
  for(int i=0; i<3; ++i){
    for(int j=0; j<2; ++j){ 
      out.csv_values += String(x[i][j]) + ", ";
    }
  }

  // formatted output
  out.format_values = ""; //resets the output string
  for(int i=0; i<3; ++i){
    for(int j=0; j<2; ++j){
      out.format_values += " " + String(i+1) + "-" + String(j+1) + ":" + String(x[i][j]);
    }
  }
  // Allows for a nicer display in Arduino IDE plotter
  out.format_values += " 0 4096  ";

  // Seconds until shutdown resets if activity is detected
  out.format_values += (last_activity_time + SHUTDOWN_TIME - millis()) / 1000;

  return out;
}