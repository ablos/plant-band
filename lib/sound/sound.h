#pragma once
#include <M5UnitSynth.h>

enum Instrument {
    // More instruments can be added, look at the documentation
    PIANO   = 0,
    ORGAN   = 19,
    FLUTE   = 73,
    STRINGS = 48
};

class Sound {
    public:
        Sound(int rxPin, int txPin);
        void begin();
        void startSound(uint8_t note, Instrument instrument = PIANO);
        void stopSound();

    private:
        M5UnitSynth synth;
        int rxPin;
        int txPin;
        uint8_t currentNote;

};