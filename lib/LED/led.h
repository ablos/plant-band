#pragma once
#include <Adafruit_NeoPixel.h>

class LED {
    public:
        LED(uint16_t count, uint8_t pin);
        void begin();
        void setBrightness(uint8_t brightness);
        void setColorRGB(uint8_t r, uint8_t g, uint8_t b);
        void setPixelRGB(uint16_t pixelIndex, uint8_t r, uint8_t g, uint8_t b);
        void setPixelRangeRGB(uint16_t lowerPixel, uint16_t upperPixel, uint8_t r, uint8_t g, uint8_t b);
        void rainbow(int delayMs);

    private:
        Adafruit_NeoPixel strip;
};