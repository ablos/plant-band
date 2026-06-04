#include <Arduino.h>
#include <sound.h>
#include <Wire.h>
#include <touch.h>

Sound sound(16, 17);

const uint8_t scale[] = {60, 62, 64, 65, 67, 69, 71}; // C D E F G A B
TouchSensor touch;

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
  Wire.begin();
  led_strip.begin();
  touch.begin(0x5A, 4);

  led_strip.setColorRGB(0, 255, 0);
}

void loop() {
  testSound();
  touch.poll(
    [](uint8_t channel) { led_strip.setPixelRGB(channel, 255, 0, 0); },
    [](uint8_t channel) { led_strip.setPixelRGB(channel, 0, 255, 0); }
  );
}


