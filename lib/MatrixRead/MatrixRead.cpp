#include "MatrixRead.h"

#include <math.h>

void MatrixRead::setup(void){
  pinMode(APIN_ORANGE, INPUT);
  pinMode(APIN_BROWN, INPUT);
  pinMode(DPIN_GREY, OUTPUT);
  pinMode(DPIN_YELLOW, OUTPUT);
  pinMode(DPIN_GREEN, OUTPUT);
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
  
  pinMode(DPIN_GREY, OUTPUT);
  digitalWrite(DPIN_GREY, HIGH);
  delay(4);
  for(int i=0; i<BUF_LEN; ++i){
    read(0, 0);
    read(0, 1);
  }
  digitalWrite(DPIN_GREY, LOW);
  pinMode(DPIN_GREY, INPUT);
  
  pinMode(DPIN_YELLOW, OUTPUT);
  digitalWrite(DPIN_YELLOW, HIGH);
  delay(4);
  for(int i=0; i<BUF_LEN; ++i){
    read(1, 0);
    read(1, 1);
  }
  digitalWrite(DPIN_YELLOW, LOW);
  pinMode(DPIN_YELLOW, INPUT);

  pinMode(DPIN_GREEN, OUTPUT);
  digitalWrite(DPIN_GREEN, HIGH);
  delay(4);
  for(int i=0; i<BUF_LEN; ++i){
    read(2, 0);
    read(2, 1);
  }
  digitalWrite(DPIN_GREEN, LOW);
  pinMode(DPIN_GREEN, INPUT);
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
      out.csv_values += x[i][j];
      out.csv_values += ", ";
    }
  }

  // formated output
  out.format_values = ""; //resets the output string
  for(int i=0; i<3; ++i){
    for(int j=0; j<2; ++j){
      out.format_values += " "; //" " + (i+1) + "-" + (j+1) + ":"
      out.format_values += i+1;
      out.format_values += "-";
      out.format_values += j+1;
      out.format_values += ":";
      out.format_values += x[i][j];
    }
  }
  // Allows for a nicer display in arduio IDE plotter
  out.format_values += " ";
  out.format_values += 0;
  out.format_values += " ";
  out.format_values += 4096;

  // Seconds until shutdown resets if activity is detected
  out.format_values += "  ";
  out.format_values += (last_activity_time + SHUTDOWN_TIME - millis()) / 1000;

  return out;
}