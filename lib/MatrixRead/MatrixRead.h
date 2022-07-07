/* MatrixRead.h
 * 23.06.2022
 * 
 * Reading the values from the input-pins and returning the values
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */
#include <Arduino.h>

#define APIN_ORANGE 33
#define APIN_BROWN 34
const int DPINS[] = {22, 21, 25};

// Class to output the read Variables, it saves the Values as a String, and in an array, it also saves the program run time.
class Output{
  public:
  // holds output as comma separated values
  String csv_values;
  // holds output with row and column an with bounds for better scaling in Arduino Serial Monitor
  String format_values;
  // holds output as an array
  uint16_t array_values[6];

  unsigned long run_time = 0;
};

// Class for reading and formatting
class MatrixRead{
  
  private:
  int BUF_LEN = 10.0;
  int SHUTDOWN_THRESHOLD;
  int SHUTDOWN_TIME;

  uint16_t x[3][2];
  unsigned int last_activity_time = 0;
  uint16_t last_activity_value[3][2];

  public: 
  Output out;
  bool shutdown_requested = false;

  MatrixRead(){
    x[3][2] = 0;
  }
  // this will set all the pins in the right mode
  void setup(int shutdown_time, int shutdown_threshold, int buf_len);
  
  // this will read the value from the given row and column
  // the result is written into the x[][] array.
  // if the value is below the THRESHOLD this will write 0
  // else this will scale the value with the SCALER
  void read(short row, short col);

  // this will get all values with the read function 
  // and put them in the array
  void get_values(void);

  // this will return the Output class
  Output get_output(void);
};