#include <Arduino.h>
#include <Wire.h>
#include <touch.h>
#include <led.h>
#include <display.h>
#include <song_player.h>
#include <songs.h>

LED led_strip = LED(41, 14);
Display display = Display(4, 5, 6, 7, 15, 16);
SongPlayer player(led_strip);
TouchSensor touch;

void setup() {
    Wire.begin();
    led_strip.begin();
    display.begin();
    display.println("Twinkle Twinkle");
}

void loop() {
    player.playSequence(TWINKLE_TWINKLE);
    delay(2000);
}


