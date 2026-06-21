#include "led.h"

LED::LED(uint16_t count, uint8_t pin) : strip(count, pin, NEO_GRB + NEO_KHZ800) {}

void LED::begin() {
    strip.begin();
    setBrightness(255);
}

void LED::setBrightness(uint8_t brightness) {
    strip.setBrightness(brightness);
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

void LED::setPixelRangeRGB(uint16_t lowerPixel, uint16_t upperPixel, uint8_t r, uint8_t g, uint8_t b) {
    for (int i = lowerPixel; i <= upperPixel; i++) {
        setPixelRGB(i, r, g, b);
    }
    strip.show();
}

void LED::setLeaves(const LeafRange *leaves, uint8_t leafCount) {
    this->leaves = leaves;
    this->leafCount = leafCount;
}

void LED::lightLeaf(uint8_t leafIndex, uint8_t r, uint8_t g, uint8_t b) {
    if (leafIndex >= leafCount) return;
    setPixelRangeRGB(leaves[leafIndex].start, leaves[leafIndex].end, r, g, b);
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