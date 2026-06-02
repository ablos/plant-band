#include <Arduino.h>
#include <led.h>

#define LED_PIN 14
#define PIXEL_COUNT 41

LED led_strip(PIXEL_COUNT, LED_PIN);

void setup() {
  led_strip.begin();
  led_strip.setColorRGB(255, 0, 0);
  led_strip.setPixelRGB(0, 0, 255, 0);
  delay(1000);
}

void loop() {
  led_strip.rainbow(5);
}