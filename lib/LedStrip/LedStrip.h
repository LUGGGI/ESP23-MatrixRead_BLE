/* Led.h
 * 01.06.2023
 * 
 * Class for using the LED on the ESP32
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */
#ifndef LED_STRIP_H
#define LED_STRIP_H

//disables output of pragma Message
#define FASTLED_INTERNAL
#include <FastLED.h>

#define LED_STRIP_PIN 26
#define NUM_LEDS 100

class Color {
  public:
  int DITF[2][3] = {
    {1, 120, 180},
    {43, 160, 70}
  };
};

class LedStrip{
  private:
  const int BLINK_FREQ = 2000; // frequency for blinking of status led in ms

  CRGB leds[NUM_LEDS];
  int blink_time;
  bool blink_state = false;

  public:
  CRGB::HTMLColorCode std_color = CRGB::Blue;
  Color color;

  // initializes led
  void setup(void);

  // Blinking for the main program, uses the std_color
  void blink();

  // Blinking if for example holding the button
  void action_blink(CRGB::HTMLColorCode color=CRGB::Green);

  // helper function to display wanted color
  void show(CRGB::HTMLColorCode color);
  
  // Blinking red for 1 sec
  void error(void);
};

#endif /* LED_STRIP_H */