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
// One harmony chord and one drum hit on the first note of every phrase,
// drums cycling through kick/snare/hihat/crash instead of repeating one pad.
const SongStep twinkleSteps[] = {
  // Twinkle twinkle little star
  {0, 0, 0}, {0, REST, REST}, {4, REST, REST}, {4, REST, REST}, {5, REST, REST}, {5, REST, REST}, {4, REST, REST},
  // How I wonder what you are
  {3, 3, 1}, {3, REST, REST}, {2, REST, REST}, {2, REST, REST}, {1, REST, REST}, {1, REST, REST}, {0, REST, REST},
  // Up above the world so high
  {4, 0, 3}, {4, REST, REST}, {3, REST, REST}, {3, REST, REST}, {2, REST, REST}, {2, REST, REST}, {1, REST, REST},
  // Like a diamond in the sky
  {4, 0, 4}, {4, REST, REST}, {3, REST, REST}, {3, REST, REST}, {2, REST, REST}, {2, REST, REST}, {1, REST, REST},
  // Twinkle twinkle little star
  {0, 0, 0}, {0, REST, REST}, {4, REST, REST}, {4, REST, REST}, {5, REST, REST}, {5, REST, REST}, {4, REST, REST},
  // How I wonder what you are
  {3, 3, 6}, {3, REST, REST}, {2, REST, REST}, {2, REST, REST}, {1, REST, REST}, {1, REST, REST}, {0, REST, REST},
};

// Frere Jacques: melody only, no harmony/drum part
const SongStep frereSteps[] = {
  {0, REST, REST}, {1, REST, REST}, {2, REST, REST}, {0, REST, REST},
  {0, REST, REST}, {1, REST, REST}, {2, REST, REST}, {0, REST, REST},
  {2, REST, REST}, {3, REST, REST}, {4, REST, REST},
  {2, REST, REST}, {3, REST, REST}, {4, REST, REST},
  {4, REST, REST}, {5, REST, REST}, {4, REST, REST}, {3, REST, REST}, {2, REST, REST}, {0, REST, REST},
  {4, REST, REST}, {5, REST, REST}, {4, REST, REST}, {3, REST, REST}, {2, REST, REST}, {0, REST, REST},
  {0, REST, REST}, {4, REST, REST}, {0, REST, REST},
  {0, REST, REST}, {4, REST, REST}, {0, REST, REST},
};

const Song songs[] = {
    {"Twinkle Twinkle", twinkleSteps, sizeof(twinkleSteps) / sizeof(SongStep)},
    {"Frere Jacques",   frereSteps,   sizeof(frereSteps)   / sizeof(SongStep)},
};

const uint8_t songCount = sizeof(songs) / sizeof(Song);
