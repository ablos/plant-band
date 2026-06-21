#pragma once
#include <M5UnitSynth.h>

enum Instrument {
    // Piano
    ACOUSTIC_GRAND_PIANO  = 0,
    BRIGHT_ACOUSTIC_PIANO = 1,
    ELECTRIC_GRAND_PIANO  = 2,
    HONKY_TONK_PIANO      = 3,
    ELECTRIC_PIANO_1      = 4,
    ELECTRIC_PIANO_2      = 5,
    HARPSICHORD           = 6,
    CLAVI                 = 7,

    // Chromatic Percussion
    CELESTA       = 8,
    GLOCKENSPIEL  = 9,
    MUSIC_BOX     = 10,
    VIBRAPHONE    = 11,
    MARIMBA       = 12,
    XYLOPHONE     = 13,
    TUBULAR_BELLS = 14,
    DULCIMER      = 15,

    // Organ
    DRAWBAR_ORGAN    = 16,
    PERCUSSIVE_ORGAN = 17,
    ROCK_ORGAN       = 18,
    CHURCH_ORGAN     = 19,
    REED_ORGAN       = 20,
    ACCORDION        = 21,
    HARMONICA        = 22,
    TANGO_ACCORDION  = 23,

    // Guitar
    ACOUSTIC_GUITAR_NYLON = 24,
    ACOUSTIC_GUITAR_STEEL = 25,
    ELECTRIC_GUITAR_JAZZ  = 26,
    ELECTRIC_GUITAR_CLEAN = 27,
    ELECTRIC_GUITAR_MUTED = 28,
    OVERDRIVEN_GUITAR     = 29,
    DISTORTION_GUITAR     = 30,
    GUITAR_HARMONICS      = 31,

    // Bass
    ACOUSTIC_BASS         = 32,
    ELECTRIC_BASS_FINGER  = 33,
    ELECTRIC_BASS_PICK    = 34,
    FRETLESS_BASS         = 35,
    SLAP_BASS_1           = 36,
    SLAP_BASS_2           = 37,
    SYNTH_BASS_1          = 38,
    SYNTH_BASS_2          = 39,

    // Strings
    VIOLIN            = 40,
    VIOLA             = 41,
    CELLO             = 42,
    CONTRABASS        = 43,
    TREMOLO_STRINGS   = 44,
    PIZZICATO_STRINGS = 45,
    ORCHESTRAL_HARP   = 46,
    TIMPANI           = 47,

    // Ensemble
    STRING_ENSEMBLE_1 = 48,
    STRING_ENSEMBLE_2 = 49,
    SYNTH_STRINGS_1   = 50,
    SYNTH_STRINGS_2   = 51,
    CHOIR_AAHS        = 52,
    VOICE_OOHS        = 53,
    SYNTH_VOICE       = 54,
    ORCHESTRA_HIT     = 55,

    // Brass
    TRUMPET       = 56,
    TROMBONE      = 57,
    TUBA          = 58,
    MUTED_TRUMPET = 59,
    FRENCH_HORN   = 60,
    BRASS_SECTION = 61,
    SYNTH_BRASS_1 = 62,
    SYNTH_BRASS_2 = 63,

    // Reed
    SOPRANO_SAX  = 64,
    ALTO_SAX     = 65,
    TENOR_SAX    = 66,
    BARITONE_SAX = 67,
    OBOE         = 68,
    ENGLISH_HORN = 69,
    BASSOON      = 70,
    CLARINET     = 71,

    // Pipe
    PICCOLO      = 72,
    FLUTE        = 73,
    RECORDER     = 74,
    PAN_FLUTE    = 75,
    BLOWN_BOTTLE = 76,
    SHAKUHACHI   = 77,
    WHISTLE      = 78,
    OCARINA      = 79,

    // Synth Lead
    LEAD_SQUARE        = 80,
    LEAD_SAWTOOTH      = 81,
    LEAD_CALLIOPE      = 82,
    LEAD_CHIFF         = 83,
    LEAD_CHARANG       = 84,
    LEAD_VOICE         = 85,
    LEAD_FIFTHS        = 86,
    LEAD_BASS_AND_LEAD = 87,

    // Synth Pad
    PAD_NEW_AGE   = 88,
    PAD_WARM      = 89,
    PAD_POLYSYNTH = 90,
    PAD_CHOIR     = 91,
    PAD_BOWED     = 92,
    PAD_METALLIC  = 93,
    PAD_HALO      = 94,
    PAD_SWEEP     = 95,

    // Synth Effects
    FX_RAIN       = 96,
    FX_SOUNDTRACK = 97,
    FX_CRYSTAL    = 98,
    FX_ATMOSPHERE = 99,
    FX_BRIGHTNESS = 100,
    FX_GOBLINS    = 101,
    FX_ECHOES     = 102,
    FX_SCI_FI     = 103,

    // Ethnic
    SITAR    = 104,
    BANJO    = 105,
    SHAMISEN = 106,
    KOTO     = 107,
    KALIMBA  = 108,
    BAGPIPE  = 109,
    FIDDLE   = 110,
    SHANAI   = 111,

    // Percussive
    TINKLE_BELL    = 112,
    AGOGO          = 113,
    STEEL_DRUMS    = 114,
    WOODBLOCK      = 115,
    TAIKO_DRUM     = 116,
    MELODIC_TOM    = 117,
    SYNTH_DRUM     = 118,
    REVERSE_CYMBAL = 119,

    // Sound Effects
    GUITAR_FRET_NOISE = 120,
    BREATH_NOISE      = 121,
    SEASHORE          = 122,
    BIRD_TWEET        = 123,
    TELEPHONE_RING    = 124,
    HELICOPTER        = 125,
    APPLAUSE          = 126,
    GUNSHOT           = 127
};

class Sound {
    public:
        void begin(int txPin);
        void setInstrument(uint8_t channel, Instrument instrument);
        void startSound(uint8_t channel, uint8_t note);
        void stopSound(uint8_t channel, uint8_t note);

    private:
        M5UnitSynth synth;

};