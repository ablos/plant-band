#pragma once
#include <LiquidCrystal.h>

class Display {
    public:
        Display(uint8_t rs, uint8_t e, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
        void begin();
        void setCursor(uint8_t x, uint8_t y);
        void print(const char* value);
        void println(const char* value);
        void clear();

    private:
        LiquidCrystal lcd;
};
