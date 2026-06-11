#include "song_player.h"
#include <Arduino.h>

static const uint8_t noteLed[] = {0, 2, 4, 6, 8, 10, 12};

SongPlayer::SongPlayer(LED& led) : _led(led) {}

void SongPlayer::playSequence(const Song& song) {
    for (int i = 0; i < song.length; i++) {
        uint8_t note = song.notes[i];
        _led.setColorRGB(0, 0, 0);
        _led.setPixelRGB(noteLed[note], song.r, song.g, song.b);
        delay(song.stepMs);
    }
    _led.setColorRGB(0, 0, 0);
}

void SongPlayer::play(const Song& song, TouchSensor& touch) {
    for (int i = 0; i < song.length; i++) {
        while (!touch.event) {}
        touch.poll([](uint8_t){}, nullptr);

        uint8_t note = song.notes[i];
        _led.setColorRGB(0, 0, 0);
        _led.setPixelRGB(noteLed[note], song.r, song.g, song.b);
    }
    _led.setColorRGB(0, 0, 0);
}
