/* gowannago.ino
 * 23.06.2022
 * 
 * Main file for the GoWannaGo project.
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */

#include <Preferences.h>
#include <BluetoothSerial.h>

#include "Settings.h"
#include "MatrixRead.h"
#include "Led.h"
#include "Ble.h"
#include "Gamepad.h"


#define SEND_FREQ 50 // send frequency in ms
#define BUTTON 39
#define POWER_PIN 19

// holds the current Mode:
// BLE_VALUES: Sensor values over Bluetooth low energy
// SERIAL_BT_VALUES: Sensor values over Serial bus with classic bluetooth
// GAMEPAD: Sensor values as BLE Gamepad joystick
Preferences preferences;
String mode = "BLE_VALUES";
Settings settings;

BluetoothSerial SerialBT;
MatrixRead matrix;
Led led;
Ble ble;
Gamepad gamepad;
Output output;	

unsigned long loop_time = 0;
int shutdown_request_time = 0;

void set_mode();
void button_action();
void shutdown(bool directly);

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);  
  
  led.setup();
  matrix.setup();

  preferences.begin("app", false);

  set_mode();
  if (mode == "BLE_VALUES"){
    led.std_color = CRGB::Blue;
    ble.setup("BLE_GoWannaGo");
  } else if (mode == "SERIAL_BT_VALUES"){
    led.std_color = CRGB::Purple;
    SerialBT.begin("Serial_GoWannaGo");
  } else {
    led.std_color = CRGB::Yellow;
    gamepad.setup();
  }
  led.show(led.std_color);
  
  settings.setup();

  delay(2000);
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
  if (mode == "BLE_VALUES"){
    ble.sent_data_raw(output.array_values);
    ble.sent_time((uint32_t) output.run_time);
  } else if (mode == "SERIAL_BT_VALUES"){
    SerialBT.println(output.format_values);
  } else {
    gamepad.update(output.array_values);
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

// set mode to value in preferences
void set_mode(){
  mode = preferences.getString("mode", "BLE_VALUES");
  Serial.print("Mode: ");
  Serial.println(mode);
}

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
  if (mode == "BLE_VALUES"){
    preferences.putString("mode", "SERIAL_BT_VALUES");
    led.std_color = CRGB::Purple;
  } else if (mode == "SERIAL_BT_VALUES"){
    preferences.putString("mode", "GAMEPAD");
    led.std_color = CRGB::Yellow;
  } else {
    preferences.putString("mode", "BLE_VALUES");
    led.std_color = CRGB::Blue;
  } 
  
  set_mode();
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
