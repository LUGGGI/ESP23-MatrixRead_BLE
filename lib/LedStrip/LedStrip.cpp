#include "LedStrip.h"

void LedStrip::setup(void){
    FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(10);
    for(int i=0; i<NUM_LEDS; ++i) {
      leds[i] = CRGB::Green;
    }
}


void LedStrip::blink(){
  if (millis() > (blink_time + BLINK_FREQ)) {
    show(std_color);
    if (millis() > (blink_time + BLINK_FREQ + 200)){
      show(CRGB::Black);
      blink_time = millis();
    }
  }
}


void LedStrip::action_blink(CRGB::HTMLColorCode color){
  if(!blink_state) {
    show(color);
  }else {
    show(CRGB::Black);
  }
  blink_state = !blink_state;
}


void LedStrip::show(CRGB::HTMLColorCode color){
    leds[0] = color;
    FastLED.show();
}


void LedStrip::error(void){
  show(CRGB::Red);
  delay(500);
  show(CRGB::Black);
  delay(500);
  show(CRGB::Blue);
}