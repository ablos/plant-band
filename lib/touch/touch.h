#pragma once
#include <Arduino.h>
#include <Adafruit_MPR121.h>
#include <Wire.h>
#include <functional>

// SDA = 8
// SCL = 9

// touch.begin(0x5A, 11);
// touch.onTouch([](uint8_t channel) { display.println((String("Touch on channel ") + channel).c_str()); });
// touch.onRelease([](uint8_t channel) { display.println((String("Release on channel ") + channel).c_str()); });

class TouchSensor {
    public:
        bool begin(uint8_t address, uint8_t irqPin, uint8_t touchThreshold = 12, uint8_t releaseThreshold = 6, TwoWire &wire = Wire);
        void loop();

        void onTouch(std::function<void(uint8_t channel)> handler) { touchHandler = handler; }
        void onRelease(std::function<void(uint8_t channel)> handler) { releaseHandler = handler; }

        volatile bool event = false;

    private:
        Adafruit_MPR121 mpr;
        uint16_t lastTouched = 0;
        std::function<void(uint8_t)> touchHandler;
        std::function<void(uint8_t)> releaseHandler;
};