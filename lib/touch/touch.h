#pragma once
#include <Arduino.h>
#include <Adafruit_MPR121.h>
#include <Wire.h>

class TouchSensor {
    public:
        bool begin(uint8_t address, uint8_t irqPin, uint8_t touchThreshold = 12, uint8_t releaseThreshold = 6, TwoWire &wire = Wire);
        void poll(void (*onTouch)(uint8_t channel), void (*onRelease)(uint8_t channel) = nullptr);

        volatile bool event = false;

    private:
        Adafruit_MPR121 mpr;
        uint16_t lastTouched = 0;
};