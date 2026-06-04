#include <Arduino.h>
#include <sound.h>

Sound sound(16, 17);

const uint8_t scale[] = {60, 62, 64, 65, 67, 69, 71}; // C D E F G A B

void setup() {
  sound.begin();
}

void testSound(){
  for (int i = 0; i < 7; i++) {
    sound.startSound(scale[i], STRINGS);
    delay(4000);
    sound.stopSound();
    delay(50);
  }
  delay(500);
}

void loop() {
  testSound();
}


