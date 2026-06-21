#pragma once
#include <Adafruit_NeoPixel.h>

struct LeafRange {
    uint16_t start;
    uint16_t end;
};

class LED {
    public:
        LED(uint16_t count, uint8_t pin);
        void begin();
        void setBrightness(uint8_t brightness);
        void setColorRGB(uint8_t r, uint8_t g, uint8_t b);
        void setPixelRGB(uint16_t pixelIndex, uint8_t r, uint8_t g, uint8_t b);
        void setPixelRangeRGB(uint16_t lowerPixel, uint16_t upperPixel, uint8_t r, uint8_t g, uint8_t b);
        void setLeaves(const LeafRange *leaves, uint8_t leafCount);
        void lightLeaf(uint8_t leafIndex, uint8_t r, uint8_t g, uint8_t b);
        void rainbow(int delayMs);

    private:
        Adafruit_NeoPixel strip;
        const LeafRange *leaves = nullptr;
        uint8_t leafCount = 0;
};