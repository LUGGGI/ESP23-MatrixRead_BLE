#include "Led.h"

void Led::setup(void){
    FastLED.addLeds<NEOPIXEL, LED_PIN>(led, 1);
    FastLED.setBrightness(10);
    show(CRGB::Green);
}


void Led::blink(){
  if (millis() > (blink_time + BLINK_FREQ)) {
    show(std_color);
    if (millis() > (blink_time + BLINK_FREQ + 200)){
      show(CRGB::Black);
      blink_time = millis();
    }
  }
}


void Led::action_blink(CRGB::HTMLColorCode color){
  if(!blink_state) {
    show(color);
  }else {
    show(CRGB::Black);
  }
  blink_state = !blink_state;
}


void Led::show(CRGB::HTMLColorCode color){
    led[0] = color;
    FastLED.show();
}


void Led::error(void){
  show(CRGB::Red);
  delay(500);
  show(CRGB::Black);
  delay(500);
  show(CRGB::Blue);
}