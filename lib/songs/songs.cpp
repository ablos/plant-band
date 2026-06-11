#include "songs.h"

static const uint8_t twinkleMelody[] = {
    N_C, N_C, N_G, N_G, N_A, N_A, N_G,
    N_F, N_F, N_E, N_E, N_D, N_D, N_C,
    N_G, N_G, N_F, N_F, N_E, N_E, N_D,
    N_G, N_G, N_F, N_F, N_E, N_E, N_D,
    N_C, N_C, N_G, N_G, N_A, N_A, N_G,
    N_F, N_F, N_E, N_E, N_D, N_D, N_C
};

const Song TWINKLE_TWINKLE = {
    "Twinkle Twinkle",
    twinkleMelody,
    sizeof(twinkleMelody),
    400,
    0, 255, 0
};

static const uint8_t piratesMelody[] = {
    // Phrase 1
    N_A, N_B, N_C, N_D, N_E, N_E, N_D, N_E, N_D, N_C, N_B, N_A,
    // Phrase 2 (Bb->F variation)
    N_A, N_B, N_C, N_D, N_E, N_F, N_E, N_D, N_E, N_D, N_C, N_B,
    // Heroic resolution
    N_A, N_C, N_E, N_A, N_G, N_F, N_E,
    N_A, N_C, N_E, N_A, N_G, N_F, N_E, N_D, N_C, N_B, N_A
};

const Song PIRATES_OF_CARIBBEAN = {
    "Pirates of Caribbean",
    piratesMelody,
    sizeof(piratesMelody),
    250,
    0, 150, 255
};
