/* Ble.h
 * 23.06.2022
 * 
 * Class for using BT Low Energy on the ESP32
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */

#ifndef BLE_H_
#define BLE_H_

#include <stdint.h>
#include <Arduino.h>

class Ble{
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

#endif /* BLE_H_ */