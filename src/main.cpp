#include <Arduino.h>
#include <Wire.h>
#include <touch.h>
#include <led.h>
#include <display.h>


const uint8_t scale[] = {60, 62, 64, 65, 67, 69, 71}; // C D E F G A B
TouchSensor touch;
LED led_strip = LED(41, 14);

Display display = Display(4, 5, 6, 7, 15, 16);

void setup() {
  Wire.begin();

  led_strip.begin();
  display.begin();
  display.println("Hello world!");
}

void loop() {
  led_strip.rainbow(10);
}


