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
  led_strip.setBrightness(100);
  led_strip.setPixelRangeRGB(10, 25, 0, 0, 255);
  delay(2000);
  led_strip.setBrightness(255);
  delay(3000);
}

void loop() {
  led_strip.rainbow(5);
}