#pragma once
#include <Arduino.h>

#define REST 255 // plant has nothing to play on this step

struct SongStep {
    uint8_t melody;  // plant A (piano) leaf, or REST
    uint8_t harmony; // plant B (guitar) leaf, or REST
    uint8_t drum;    // plant C leaf, or REST
};

struct Song {
    const char *name;
    const SongStep *steps;
    uint8_t stepCount;
};

// Twinkle Twinkle Little Star: 6 phrases of 7 notes each.
// All three plants play the same note on every step (unison).
const SongStep twinkleSteps[] = {
  // Twinkle twinkle little star
  {0, 0, 0}, {0, 0, 0}, {4, 4, 4}, {4, 4, 4}, {5, 5, 5}, {5, 5, 5}, {4, 4, 4},
  // How I wonder what you are
  {3, 3, 3}, {3, 3, 3}, {2, 2, 2}, {2, 2, 2}, {1, 1, 1}, {1, 1, 1}, {0, 0, 0},
  // Up above the world so high
  {4, 4, 4}, {4, 4, 4}, {3, 3, 3}, {3, 3, 3}, {2, 2, 2}, {2, 2, 2}, {1, 1, 1},
  // Like a diamond in the sky
  {4, 4, 4}, {4, 4, 4}, {3, 3, 3}, {3, 3, 3}, {2, 2, 2}, {2, 2, 2}, {1, 1, 1},
  // Twinkle twinkle little star
  {0, 0, 0}, {0, 0, 0}, {4, 4, 4}, {4, 4, 4}, {5, 5, 5}, {5, 5, 5}, {4, 4, 4},
  // How I wonder what you are
  {3, 3, 3}, {3, 3, 3}, {2, 2, 2}, {2, 2, 2}, {1, 1, 1}, {1, 1, 1}, {0, 0, 0},
};

// Frere Jacques: all three plants play the same note on every step (unison)
const SongStep frereSteps[] = {
  {0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {0, 0, 0},
  {0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {0, 0, 0},
  {2, 2, 2}, {3, 3, 3}, {4, 4, 4},
  {2, 2, 2}, {3, 3, 3}, {4, 4, 4},
  {4, 4, 4}, {5, 5, 5}, {4, 4, 4}, {3, 3, 3}, {2, 2, 2}, {0, 0, 0},
  {4, 4, 4}, {5, 5, 5}, {4, 4, 4}, {3, 3, 3}, {2, 2, 2}, {0, 0, 0},
  {0, 0, 0}, {4, 4, 4}, {0, 0, 0},
  {0, 0, 0}, {4, 4, 4}, {0, 0, 0},
};

const Song songs[] = {
    {"Twinkle Twinkle", twinkleSteps, sizeof(twinkleSteps) / sizeof(SongStep)},
    {"Frere Jacques",   frereSteps,   sizeof(frereSteps)   / sizeof(SongStep)},
};

const uint8_t songCount = sizeof(songs) / sizeof(Song);
