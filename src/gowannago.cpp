/* gowannago.ino
 * 23.06.2022
 * 
 * Main file for the GoWannaGo project.
 * This program allows the controller (m5Stack Atom) to read resistance values 
 * from a mat or ribbon. It will filter with a moving average and send those 
 * values over bluetooth. There are 3 modi for sending available:
 * - Over BLE (BT low energy), all parallel measured values are sent as one
 * - Over classic BT, values as formatted string for serial bus
 * - Over BLE as Gamepad, controller show up as a gamepad
 * All Values are sent as 16 bit unsigned integer.
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
//das wäre schön Version: https://community.platformio.org/t/how-to-build-got-revision-into-binary-for-version-output/15380/5
// oder hier: https://community.platformio.org/t/platformio-version-increment/13945/3
#define VERSION "Version 1.0 (platformio)"
#define PRINTPROJINFO() 	Serial.println(F("compiled: " __DATE__ " " __TIME__ ":\r\n" __FILE__ ));
#define PRINTIDEINFO() 		Serial.print(F("IDE: "));  Serial.println((ARDUINO));


Settings set;

BluetoothSerial SerialBT;
MatrixRead matrix;
Led led;
Ble ble;
Gamepad gamepad;
Output output;	

unsigned long loop_time = 0;
int shutdown_request_time = 0;

void button_action();
void shutdown(bool directly);

void setup() {
  Serial.begin(115200);
  setCpuFrequencyMhz(80); // cpu frequency to 80 mHz (set to 160 or 240 if send frequency can't be met)
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);  
  
  led.setup();
  set.setup();
  matrix.setup(set.SHUTDOWN_TIME, set.SHUTDOWN_THRESHOLD, set.BUF_LEN);

  if (set.CONTROLLER_MODE == "BLE_VALUES"){
    led.std_color = CRGB::Blue;
    String name = String(set.ID) + "_BLE_GoWannaGo";
    ble.setup(name.c_str());
  } else if (set.CONTROLLER_MODE == "SERIAL_BT_VALUES"){
    led.std_color = CRGB::Purple;
    String name = String(set.ID) + "_Serial_GoWannaGo";
    SerialBT.begin(name);
  } else {
    led.std_color = CRGB::Yellow;
    String name = String(set.ID) + "_BLE_Gamepad";
    gamepad.setup(name, matrix);
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

  Serial.print(output.format_values);
  // Send data
  if (set.CONTROLLER_MODE == "BLE_VALUES"){
    ble.sent_data_raw(output.output_array);
    ble.sent_time((uint32_t) output.run_time);
  } else if (set.CONTROLLER_MODE == "SERIAL_BT_VALUES"){
    SerialBT.println(output.format_values);
  } else {
    gamepad.update(output.output_array);
  }

  // check frequency
  if (millis() > (loop_time + set.SEND_FREQ)) {
    Serial.print("Error SEND_FREQUENCY to low");
    led.error();
  }
  led.blink();
  // wait for next send freq
  while((millis() < (loop_time + set.SEND_FREQ)) && digitalRead(BUTTON)){
    delay(1);
  }
  Serial.println();
}


///////////////////////////////////////////////////////////////////////
// Methods

//print long line of chars
void SerialprintChar(const char a,uint16_t n)
{
  for(int i=0;i<n;i++)
  {
     Serial.print(a);
  }
  Serial.println();   
}

// controls what happens if the BUTTON is pressed
void button_action(){
  Serial.println();Serial.println();
  SerialprintChar('#',80);
  Serial.println(VERSION);
  PRINTPROJINFO();
  PRINTIDEINFO();
  SerialprintChar('#',80);
  Serial.println();
  Serial.println("Button pressed");
  unsigned long button_time = millis();

  while(!digitalRead(BUTTON)){
    led.action_blink();

    if (millis() > (button_time + 3000)) shutdown(true);
    else delay(200);
  }

  // change mode
  if (set.CONTROLLER_MODE == "BLE_VALUES"){
    set.save_mode("SERIAL_BT_VALUES");
    led.std_color = CRGB::Purple;
  } else if (set.CONTROLLER_MODE == "SERIAL_BT_VALUES"){
    set.save_mode("GAMEPAD");
    led.std_color = CRGB::Yellow;
  } else {
    set.save_mode("BLE_VALUES");
    led.std_color = CRGB::Blue;
  } 

  led.show(led.std_color);
  ESP.restart();
}

// controls the shutdown
void shutdown(bool directly) {
  if (shutdown_request_time == 0){
    Serial.println("Shutdown Requested");
    shutdown_request_time = millis();
  }
  led.action_blink();

  if ((millis() > shutdown_request_time + 10000) || directly){
    Serial.println("Controller off");
    digitalWrite(POWER_PIN, LOW);
    led.show(CRGB::Red);
    while(true){}
  }
}
