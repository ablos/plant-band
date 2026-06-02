#include "led.h"

LED::LED(uint16_t count, uint8_t pin) : strip(count, pin, NEO_GRB + NEO_KHZ800) {}

void LED::begin() {
    strip.begin();
    strip.setBrightness(255);
    strip.show();
}

void LED::setPixelRGB(uint16_t pixelIndex, uint8_t r, uint8_t g, uint8_t b) {
    strip.setPixelColor(pixelIndex, strip.Color(r, g, b));
    strip.show();
}

void LED::setColorRGB(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < strip.numPixels(); i++) {
        setPixelRGB(i, r, g, b);
    }
    strip.show();
}

void LED::rainbow(int delayMs) {
    for (long hue = 0; hue < 65536; hue += 256) {
        for (int i = 0; i < strip.numPixels(); i++) {
            int pixelHue = hue + (i * 65536L / strip.numPixels());
            strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }

        strip.show();
        delay(delayMs);
    }
}