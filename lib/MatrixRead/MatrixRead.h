/* MatrixRead.h
 * 19.10.2022 
 * 
 * Reading the values from the input-pins and returning the values
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */
#ifndef MATRIX_READ_H
#define MATRIX_READ_H

#include <Arduino.h>

const int COLS = 3;
const int ROWS = 2;
const int FIELDS = COLS*ROWS;

// Class to output the read Variables, it saves the Values as a String, and in an array, it also saves the program run time.
class Output{
  public:
  // holds output as comma separated values
  String csv_values;
  // holds output with row and column an with bounds for better scaling in Arduino Serial Monitor
  String format_values;
  // holds output as an array
  uint16_t output_array[FIELDS];

  unsigned long run_time = 0;
};

// Class for reading and formatting
class MatrixRead{
  
  private:
  const int A_PIN_ORANGE = 33;
  const int A_PIN_BROWN = 34;
  const int D_PINS[3] = {22, 21, 25};

  uint32_t BUF_LEN;
  int SHUTDOWN_THRESHOLD;
  int SHUTDOWN_TIME;

  uint32_t buffer[COLS][ROWS];
  unsigned int last_activity_time = 0;
  uint32_t last_activity_value[COLS][ROWS];

  public: 
  Output out;
  bool shutdown_requested = false;

  // this will set all the pins in the right mode
  void setup(int _SHUTDOWN_TIME, int _SHUTDOWN_THRESHOLD, int _BUF_LEN);
  
  // this will read the value from the given row and column
  // the result is written into the buffer[][] array.
  // if the value is below the THRESHOLD this will write 0
  // else this will scale the value with the SCALER
  void read(short row, short col);

  // this will get all values with the read function 
  // and put them in the array
  void get_values(void);

  // this will return the Output class
  Output get_output(void);
};

#endif /* MATRIX_READ_H */