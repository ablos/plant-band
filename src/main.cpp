#include <Arduino.h>
#include <Wire.h>
#include <touch.h>
#include <led.h>
#include <display.h>
#include <knob.h>
#include <sound.h>
#include <songs.h>

const uint8_t scale[] = {60, 62, 64, 65, 67, 69, 71, 72};
const uint8_t drumNotes[] = {36, 38, 39, 42, 46, 45, 49, 51};

const LeafRange leaves[] = {
  {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}
};

const LeafRange leavesA[] = {
  {0, 1}, {2, 3}, {4, 5}, {6, 6}, {7, 8}, {9, 9}, {10, 11}, {12, 12}
};

struct RGB { uint8_t r, g, b; };

// one color per leaf/note, shared by all three plants in freeplay
const RGB noteColors[8] = {
  {255,   0,   0},
  {255,  90,   0},
  {255, 200,   0},
  {  0, 200,   0},
  {  0, 200, 180},
  {  0,  80, 255},
  { 80,   0, 255},
  {200,   0, 200},
};

#define IDLE_DIM_DIV 8 // freeplay idle brightness = touch brightness / this

RGB dimColor(RGB c) {
  return { (uint8_t)(c.r / IDLE_DIM_DIV), (uint8_t)(c.g / IDLE_DIM_DIV), (uint8_t)(c.b / IDLE_DIM_DIV) };
}

#define ENCODER_A_PIN 18
#define ENCODER_B_PIN 17
#define ENCODER_BTN_PIN 10

#define TOUCH_IRQ_A 21
#define TOUCH_IRQ_B 2
#define TOUCH_IRQ_C 1

Display display = Display(4, 5, 6, 7, 15, 16);
Knob knob;
Sound synth;

LED led_a = LED(13, 11);
LED led_b = LED(8, 12);
LED led_c = LED(8, 13);

TouchSensor touch_a;
TouchSensor touch_b;
TouchSensor touch_c;

#define MENU_IDLE_TIMEOUT_MS 4000 // revert to freeplay after this long without knob activity in song/instrument select

int8_t selectedSong = 0;
bool songMode = false;
bool browsingMenu = false; // true while the song/instrument select screens are showing
bool selectingInstruments = false;
uint8_t instrumentCount = 3; // how many plants take part in the song: 1 = melody only, 2 = +harmony, 3 = +drum
unsigned long lastMenuActivity = 0;
uint8_t songStep = 0;
bool stepMelodyDone = false, stepHarmonyDone = false, stepDrumDone = false;

bool harmonyActive() { return instrumentCount >= 2; }
bool drumActive()    { return instrumentCount >= 3; }

void playStartupChime();
void handleTouchA(uint8_t channel);
void handleTouchB(uint8_t channel);
void handleTouchC(uint8_t channel);
void handleReleaseA(uint8_t channel);
void handleReleaseB(uint8_t channel);
void handleReleaseC(uint8_t channel);
void refreshPlantLed(LED &led, uint8_t current, uint8_t next, bool done);
void refreshLedA();
void refreshLedB();
void refreshLedC();
void applyStep();
void advanceStepIfReady();
void startSong();
void stopSong();
void showFreeplayIdle();
void showFreeplayStatus();
void showSongSelect();
void showSongProgress();
void showInstrumentSelect();
void enterMenu();

void setup() {
  // Start i2c
  Wire.begin();

  // Start LEDs
  led_a.begin();
  led_b.begin();
  led_c.begin();

  led_a.setLeaves(leavesA, 8);
  led_b.setLeaves(leaves, 8);
  led_c.setLeaves(leaves, 8);
  showFreeplayIdle();

  // Start Display
  display.begin();
  display.println("Welcome to PlantBand!");

  // Start synth
  synth.begin(14);
  playStartupChime();
  synth.setInstrument(0, ACOUSTIC_GRAND_PIANO);
  synth.setInstrument(1, ACOUSTIC_GUITAR_NYLON);
  //synth.setInstrument(2, STRING_ENSEMBLE_1);

  // Start knob
  knob.begin(ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_BTN_PIN);
  knob.onRotate([](int delta) {
    lastMenuActivity = millis();
    if (selectingInstruments) {
      instrumentCount = ((instrumentCount - 1 + (delta > 0 ? 1 : -1) + 3) % 3) + 1;
      showInstrumentSelect();
      return;
    }
    stopSong();
    bool wasBrowsing = browsingMenu;
    enterMenu();
    if (wasBrowsing) {
      selectedSong = (selectedSong + songCount + (delta > 0 ? 1 : -1)) % songCount;
    }
    showSongSelect();
  });
  knob.onPress([]() {
    lastMenuActivity = millis();
    if (songMode) {
      stopSong();
      browsingMenu = false;
      selectingInstruments = false;
      return;
    }
    if (selectingInstruments) {
      selectingInstruments = false;
      browsingMenu = false;
      startSong();
      return;
    }
    enterMenu();
    selectingInstruments = true;
    instrumentCount = 3;
    showInstrumentSelect();
  });

  // Start touch
  touch_a.begin(0x5A, 21, 20, 14);
  touch_b.begin(0x5B, 2, 20, 14);
  touch_c.begin(0x5C, 1, 20, 14);

  touch_a.onTouch(handleTouchA);
  touch_a.onRelease(handleReleaseA);

  touch_b.onTouch(handleTouchB);
  touch_b.onRelease(handleReleaseB);

  touch_c.onTouch(handleTouchC);
  touch_c.onRelease(handleReleaseC);

  delay(1000);
  showFreeplayStatus();
}

void loop() {
  knob.loop();
  touch_a.loop();
  touch_b.loop();
  touch_c.loop();

  if (browsingMenu && millis() - lastMenuActivity > MENU_IDLE_TIMEOUT_MS) {
    browsingMenu = false;
    selectingInstruments = false;
    showFreeplayStatus();
  }
}

void handleTouchA(uint8_t channel) {
  if (channel >= 8) return;
  synth.startSound(0, scale[channel]);

  if (!songMode) {
    led_a.lightLeaf(channel, noteColors[channel].r, noteColors[channel].g, noteColors[channel].b);
    return;
  }
  if (stepMelodyDone) return; // already played this step, just waiting on the others

  bool correct = songs[selectedSong].steps[songStep].melody == channel;
  led_a.lightLeaf(channel, correct ? 0 : 255, correct ? 255 : 0, 0);
  if (correct) stepMelodyDone = true;
}
void handleReleaseA(uint8_t channel) {
  if (channel >= 8) return;
  synth.stopSound(0, scale[channel]);

  if (!songMode) {
    RGB c = dimColor(noteColors[channel]);
    led_a.lightLeaf(channel, c.r, c.g, c.b);
    return;
  }

  led_a.lightLeaf(channel, 0, 0, 0);
  delay(100);
  advanceStepIfReady();
  if (songMode) refreshLedA();
}

void handleTouchB(uint8_t channel) {
  if (channel >= 8) return;
  synth.startSound(1, scale[channel] + 12);

  if (!songMode) {
    led_b.lightLeaf(channel, noteColors[channel].r, noteColors[channel].g, noteColors[channel].b);
    return;
  }
  if (stepHarmonyDone) return;

  bool correct = songs[selectedSong].steps[songStep].harmony == channel;
  led_b.lightLeaf(channel, correct ? 0 : 255, correct ? 255 : 0, 0);
  if (correct) stepHarmonyDone = true;
}
void handleReleaseB(uint8_t channel) {
  if (channel >= 8) return;
  synth.stopSound(1, scale[channel] + 12);

  if (!songMode) {
    RGB c = dimColor(noteColors[channel]);
    led_b.lightLeaf(channel, c.r, c.g, c.b);
    return;
  }

  led_b.lightLeaf(channel, 0, 0, 0);
  delay(100);
  advanceStepIfReady();
  if (songMode) refreshLedB();
}

void handleTouchC(uint8_t channel) {
  if (channel >= 8) return;
  //synth.startSound(2, scale[channel] + 24);
  synth.startSound(9, drumNotes[channel]);

  if (!songMode) {
    led_c.lightLeaf(channel, noteColors[channel].r, noteColors[channel].g, noteColors[channel].b);
    return;
  }
  if (stepDrumDone) return;

  bool correct = songs[selectedSong].steps[songStep].drum == channel;
  led_c.lightLeaf(channel, correct ? 0 : 255, correct ? 255 : 0, 0);
  if (correct) stepDrumDone = true;
}
void handleReleaseC(uint8_t channel) {
  if (channel >= 8) return;
  //synth.stopSound(2, scale[channel] + 24);
  synth.stopSound(9, drumNotes[channel]);

  if (!songMode) {
    RGB c = dimColor(noteColors[channel]);
    led_c.lightLeaf(channel, c.r, c.g, c.b);
    return;
  }

  led_c.lightLeaf(channel, 0, 0, 0);
  delay(100);
  advanceStepIfReady();
  if (songMode) refreshLedC();
}

// current note: blue while this plant still needs to play it.
// next note: previewed in yellow on its own leaf as soon as it differs from the current one;
// if the next note repeats the current leaf, that leaf only turns yellow once it's actually
// been played (can't show blue and yellow on the same leaf at once).
void refreshPlantLed(LED &led, uint8_t current, uint8_t next, bool done) {
  led.setColorRGB(0, 0, 0); // clear any leftover freeplay rainbow / previous step's leaves

  if (current != REST && !done) {
    led.lightLeaf(current, 0, 120, 255);
  }

  if (next == REST) return;
  RGB preview = dimColor({255, 220, 0});
  if (next == current) {
    if (done) led.lightLeaf(next, preview.r, preview.g, preview.b);
  } else {
    led.lightLeaf(next, preview.r, preview.g, preview.b);
  }
}

void refreshLedA() {
  const Song &song = songs[selectedSong];
  uint8_t next = (songStep + 1 < song.stepCount) ? song.steps[songStep + 1].melody : REST;
  refreshPlantLed(led_a, song.steps[songStep].melody, next, stepMelodyDone);
}
void refreshLedB() {
  if (!harmonyActive()) { led_b.setColorRGB(0, 0, 0); return; }
  const Song &song = songs[selectedSong];
  uint8_t next = (songStep + 1 < song.stepCount) ? song.steps[songStep + 1].harmony : REST;
  refreshPlantLed(led_b, song.steps[songStep].harmony, next, stepHarmonyDone);
}
void refreshLedC() {
  if (!drumActive()) { led_c.setColorRGB(0, 0, 0); return; }
  const Song &song = songs[selectedSong];
  uint8_t next = (songStep + 1 < song.stepCount) ? song.steps[songStep + 1].drum : REST;
  refreshPlantLed(led_c, song.steps[songStep].drum, next, stepDrumDone);
}

// sets up the shared current step: parts with nothing to play (or not taking part this round) are auto-marked done
void applyStep() {
  const SongStep &step = songs[selectedSong].steps[songStep];
  stepMelodyDone  = (step.melody  == REST);
  stepHarmonyDone = (step.harmony == REST) || !harmonyActive();
  stepDrumDone    = (step.drum    == REST) || !drumActive();
  refreshLedA();
  refreshLedB();
  refreshLedC();
  showSongProgress();
}

// only the last instrument to finish the current step triggers the advance
void advanceStepIfReady() {
  if (!(stepMelodyDone && stepHarmonyDone && stepDrumDone)) return;
  songStep++;
  if (songStep >= songs[selectedSong].stepCount) {
    stopSong();
  } else {
    applyStep();
  }
}

void startSong() {
  songMode = true;
  songStep = 0;
  applyStep();
}

void stopSong() {
  songMode = false;
  showFreeplayIdle();
  showFreeplayStatus();
}

void showFreeplayIdle() {
  for (uint8_t i = 0; i < 8; i++) {
    RGB c = dimColor(noteColors[i]);
    led_a.lightLeaf(i, c.r, c.g, c.b);
    led_b.lightLeaf(i, c.r, c.g, c.b);
    led_c.lightLeaf(i, c.r, c.g, c.b);
  }
}

void showFreeplayStatus() {
  char line1[17];
  snprintf(line1, sizeof(line1), "%-16s", "Freeplay active");
  char full[40];
  snprintf(full, sizeof(full), "%sTouch a leaf!", line1);
  display.println(full);
}

void showSongSelect() {
  char label[17];
  snprintf(label, sizeof(label), "Select song %d/%d", selectedSong + 1, songCount);
  char line1[17];
  snprintf(line1, sizeof(line1), "%-16s", label);
  char full[48];
  snprintf(full, sizeof(full), "%s%s", line1, songs[selectedSong].name);
  display.println(full);
}

void showSongProgress() {
  char line1[17];
  snprintf(line1, sizeof(line1), "%-16s", songs[selectedSong].name);
  char full[48];
  snprintf(full, sizeof(full), "%sStep %d/%d", line1, songStep + 1, songs[selectedSong].stepCount);
  display.println(full);
}

void showInstrumentSelect() {
  char label[17];
  snprintf(label, sizeof(label), "Instruments: %d", instrumentCount);
  char line1[17];
  snprintf(line1, sizeof(line1), "%-16s", label);
  char full[48];
  snprintf(full, sizeof(full), "%s%s", line1, songs[selectedSong].name);
  display.println(full);
}

// enters the song/instrument select flow fresh: resets to song 1 so the scroll never remembers last time
void enterMenu() {
  if (browsingMenu) return;
  browsingMenu = true;
  selectedSong = 0;
}

void playStartupChime() {
  synth.setInstrument(0, KALIMBA);
  synth.setInstrument(1, PAD_WARM);

  const uint8_t melody[]     = {60, 64, 67, 72};  // C E G C
  const uint8_t harmony[]    = {64, 67, 71, 76};  // E G B E - a third above
  const uint16_t durations[] = {90, 90, 90, 350};  // quick, quick, quick, held landing note
  const uint16_t gaps[]      = {30, 30, 30, 150};  // breathing room before the next note

  for (uint8_t i = 0; i < 4; i++) {
    synth.startSound(0, melody[i]);
    synth.startSound(1, harmony[i]);
    delay(durations[i]);
    synth.stopSound(0, melody[i]);
    synth.stopSound(1, harmony[i]);
    delay(gaps[i]);
  }

  synth.startSound(9, 81); // soft triangle ting
  delay(250);
  synth.stopSound(9, 81);
}