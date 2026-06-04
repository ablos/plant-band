#include "sound.h"

#define SYNTH_RX 16
#define SYNTH_TX 17


Sound::Sound(int rxPin, int txPin) : rxPin(rxPin), txPin(txPin), currentNote(0) {}

void Sound::begin() {
    Serial2.begin(31250, SERIAL_8N1, rxPin, txPin);
    synth.begin(&Serial2);
    synth.setMasterVolume(200);
    synth.setInstrument(0, 0, 16); // 16 = Drawbar Organ, holds steady
}

void Sound::startSound(uint8_t note, Instrument instrument) {
    currentNote = note;
    synth.setInstrument(0, 0, instrument);
    // 127 is the intensity
    synth.setNoteOn(0, note, 127);
}

void Sound::stopSound() {
    synth.setNoteOff(0, currentNote, 0);
}