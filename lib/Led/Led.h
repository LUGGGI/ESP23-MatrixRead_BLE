/* Led.h
 * 23.06.2022
 * 
 * Class for using the LED on the ESP32
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */

//disables output of pragma Message
#define FASTLED_INTERNAL
#include <FastLED.h>

#define LED_PIN 27
#define BLINK_FREQ 2000 // frequency if the status led blinking

class Led{
  private:
  CRGB led[1];
  int blink_time;
  bool blink_state = false;

  public:
  CRGB::HTMLColorCode std_color = CRGB::Blue;
  void setup(void);
  void show(CRGB::HTMLColorCode color);
  void error(void);
  // Blinking for the main program, uses the std_color
  void blink();
  // Blinking if for example holding the button
  void action_blink(CRGB::HTMLColorCode color=CRGB::Green);
};


