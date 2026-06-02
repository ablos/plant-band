#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 14
#define PIXEL_COUNT 41

Adafruit_NeoPixel led_strip(PIXEL_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  led_strip.begin();
  led_strip.setBrightness(255);

  // Set all pixels to red
  for (int i = 0; i < PIXEL_COUNT; i++) {
    led_strip.setPixelColor(i, led_strip.Color(255, 255, 255));
  }

  led_strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
}