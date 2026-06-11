#pragma once
#include <led.h>
#include <touch.h>

#define N_C 0
#define N_D 1
#define N_E 2
#define N_F 3
#define N_G 4
#define N_A 5
#define N_B 6

struct Song {
    const char* name;
    const uint8_t* notes;
    uint8_t length;
    int stepMs;
    uint8_t r, g, b;
};

class SongPlayer {
public:
    SongPlayer(LED& led);
    void playSequence(const Song& song);
    void play(const Song& song, TouchSensor& touch);

private:
    LED& _led;
};
