#include "sound.h"

void Sound::begin(int txPin) {
    synth.begin(&Serial2, UNIT_SYNTH_BAUD, -1, txPin);
    synth.setMasterVolume(127);
}

void Sound::setInstrument(uint8_t channel, Instrument instrument) {
    synth.setInstrument(0, channel, instrument);
}

void Sound::startSound(uint8_t channel, uint8_t note) {
    synth.setNoteOn(channel, note, 127);
}

void Sound::stopSound(uint8_t channel, uint8_t note) {
    synth.setNoteOff(channel, note, 0);
}