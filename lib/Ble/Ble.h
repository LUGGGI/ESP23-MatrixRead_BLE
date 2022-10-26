/* Ble.h
 * 19.10.2022
 * 
 * Class for using BT Low Energy on the ESP32
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */

#ifndef BLE_H
#define BLE_H

#include <Arduino.h>




class Ble{
  private:
  const char* SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
  const char* VAL_UUID     = "7a7b95b1-4423-4e36-aaf4-d3698f06e38d";
  const char* TIME_UUID    = "0e5f194e-8bf3-4f68-8203-33f2ed28c49a";
  
  public:

  // Use this to setup BLE
  void setup(String name);

  // This will send Data given as a string
  void sent_data(String data);

  // This will send data/ the time given as an (uint32_t) integer
  void sent_time(uint32_t data);

  // This will send data given as an array with length 6 as one value
  void sent_data_raw(uint16_t* arr);

  // This will be called when there is no connection to host
  // will be called from setup and sent functions, so there is no need to call it separately
  void connection_event(void);

};

#endif /* BLE_H */