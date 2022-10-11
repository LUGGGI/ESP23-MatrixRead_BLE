#include "MatrixRead.h"


void MatrixRead::setup(int shutdown_time, int shutdown_threshold, int buf_len){
  SHUTDOWN_TIME = shutdown_time * 1000;
  SHUTDOWN_THRESHOLD = shutdown_threshold;
  BUF_LEN = buf_len;
  pinMode(A_PIN_ORANGE, INPUT);
  pinMode(A_PIN_BROWN, INPUT);

  for (int i=0; i<3; ++i){
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
  else exit(0);
}


void MatrixRead::get_values(void){
  out.run_time = millis();

  // set array to zero
  for(int i=0; i<3; ++i){
    for(int j=0; j<2; ++j){
      buffer[i][j] = 0;
    }
  }
  for (int i=0; i<3; ++i){
    pinMode(D_PINS[i], OUTPUT);
    digitalWrite(D_PINS[i], HIGH);
    delay(4);
    for(int j=0; j<BUF_LEN; ++j){
      read(i, 0);
      read(i, 1);
    }
    digitalWrite(D_PINS[i], LOW);
    pinMode(D_PINS[i], INPUT);
  }
}


Output MatrixRead::get_output(void){
  bool over_threshold = false;
  // fill output array
  for(int i=0; i<3; ++i){
    for(int j=0; j<2; ++j){
      buffer[i][j] /= (uint32_t) BUF_LEN;
      out.output_array[i*2+j] = (uint16_t) buffer[i][j];

      // check if activity is detected (values leave the SHUTDOWN_THRESHOLD range)
      if (abs(out.output_array[i*2+j] - last_activity_value[i][j]) > SHUTDOWN_THRESHOLD){
        last_activity_value[i][j] = out.output_array[i*2+j];
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
  for(int i=0; i<3; ++i){
    for(int j=0; j<2; ++j){ 
      out.csv_values += String(buffer[i][j]) + ", ";
    }
  }

  // formatted output
  out.format_values = ""; //resets the output string
  for(int i=0; i<3; ++i){
    for(int j=0; j<2; ++j){
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