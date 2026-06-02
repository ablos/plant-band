#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 14
#define PIXEL_COUNT 41

Adafruit_NeoPixel led_strip(PIXEL_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int colorIndex = 0;

void setup() {
  led_strip.begin();
  led_strip.setBrightness(255);

  // Set all pixels to red
  for (int i = 0; i < PIXEL_COUNT; i++) {
    led_strip.setPixelColor(i, led_strip.Color(0, 0, 0));
  }

  led_strip.show();
}

void loop() {
  for (long hue = 0; hue < 65536; hue += 256) {
    for (int i = 0; i < led_strip.numPixels(); i++) {
      int pixelHue = hue + (i * 65536L / led_strip.numPixels());
      led_strip.setPixelColor(i, led_strip.gamma32(led_strip.ColorHSV(pixelHue)));
    }

    led_strip.show();
    delay(10);
  }
}