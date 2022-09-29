/* gowannago.ino
 * 23.06.2022
 * 
 * Main file for the GoWannaGo project.
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */

#include <BluetoothSerial.h>

#include "Settings.h"
#include "MatrixRead.h"
#include "Led.h"
#include "Ble.h"
#include "Gamepad.h"


#define BUTTON 39
#define POWER_PIN 19

Settings settings;

BluetoothSerial SerialBT;
MatrixRead matrix;
Led led;
Ble ble;
Gamepad gamepad;
Output output;	

int SEND_FREQ; // send frequency in ms
unsigned long loop_time = 0;
int shutdown_request_time = 0;

void button_action();
void shutdown(bool directly);

void setup() {
  Serial.begin(115200);
  // cpu frequency to 80 mHz (set to 160 or 240 if send frequency cant be met)
  setCpuFrequencyMhz(80);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);  
  
  led.setup();
  led.show(CRGB::Green);

  settings.setup();
  SEND_FREQ = settings.send_freq;

  matrix.setup(settings.shutdown_time, settings.shutdown_threshold, settings.buf_len);

  settings.mode == "_BLE_Gamepad";

  if (settings.mode == "BLE_VALUES"){
    led.std_color = CRGB::Blue;
    String name = String(settings.id) + "_BLE_GoWannaGo";
    ble.setup(name.c_str());
  } else if (settings.mode == "SERIAL_BT_VALUES"){
    led.std_color = CRGB::Purple;
    String name = String(settings.id) + "_Serial_GoWannaGo";
    SerialBT.begin(name);
  } else {
    led.std_color = CRGB::Yellow;
    String name = String(settings.id) + "_BLE_Gamepad";
    gamepad.setup(name);
  }
  led.show(led.std_color);
  Serial.println("Controller Setup complete");
}


void loop() {
  // change mode or turn off
  if(!digitalRead(BUTTON)) button_action();

  // makes automatic shutdown possible
  if (matrix.shutdown_requested) shutdown(false);
  else shutdown_request_time = 0;

  loop_time = millis();
  
  // get data from sensor
  matrix.get_values();
  output = matrix.get_output();

  Serial.println(output.format_values);
  // Send data
  if (settings.mode == "BLE_VALUES"){
    ble.sent_data_raw(output.output_array);
    ble.sent_time((uint32_t) output.run_time);
  } else if (settings.mode == "SERIAL_BT_VALUES"){
    SerialBT.println(output.format_values);
  } else {
    gamepad.update(output.output_array);
  }

  // check frequency
  if (millis() > (loop_time + SEND_FREQ)) {
    Serial.print("Error SEND_FREQUENCY to low");
    led.error();
  }
  led.blink();
  // wait for next send freq
  while((millis() < (loop_time + SEND_FREQ)) && digitalRead(BUTTON)){
    delay(1);
  }
}


///////////////////////////////////////////////////////////////////////
// Methods

// controls what happens if the BUTTON is pressed
void button_action(){
  Serial.println("activated");
  int button_time = millis();
  bool blink_status = false;

  while(!digitalRead(BUTTON)){
    // blink to indicate that in 3 seconds the controller will turn of
    led.action_blink();

    if(millis() > (button_time + 3000)){
      shutdown(true);
      return;
    }
    delay(200);
  }

  // change mode
  if (settings.mode == "BLE_VALUES"){
    settings.save_mode("SERIAL_BT_VALUES");
    led.std_color = CRGB::Purple;
  } else if (settings.mode == "SERIAL_BT_VALUES"){
    settings.save_mode("GAMEPAD");
    led.std_color = CRGB::Yellow;
  } else {
    settings.save_mode("BLE_VALUES");
    led.std_color = CRGB::Blue;
  } 

  led.show(led.std_color);
  delay(1000);
  ESP.restart();
}

// controls the shutdown
void shutdown(bool directly) {
  if (shutdown_request_time == 0){
    Serial.println("Shutdown Requested");
    // SerialBT.println("Shutdown Requested");
    shutdown_request_time = millis();
  }
  led.action_blink();

  if ((millis() > shutdown_request_time + 10000) || directly){
    Serial.println("Controller off");
    // SerialBT.println("Controller off");
    digitalWrite(POWER_PIN, LOW);
    led.show(CRGB::Red);
    while(true){}
  }
}
