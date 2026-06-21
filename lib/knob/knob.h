#pragma once
#include <ESP32Encoder.h>
#include <Button2.h>
#include <functional>

//  knob.begin(ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_BTN_PIN);
//   knob.onRotate([](int delta) {
//     display.println(delta > 0 ? "CW" : "CCW");
//   });
//   knob.onPress([]() {
//     display.println("button");
//   });

class Knob {
public:
    bool begin(uint8_t aPin, uint8_t bPin, uint8_t btnPin);
    void loop();

    void onRotate(std::function<void(int delta)> handler) { rotateHandler = handler; }
    void onPress(std::function<void()> handler) { pressHandler = handler; }

private:
    long lastCount = 0;
    ESP32Encoder encoder;
    Button2 button;
    std::function<void(int)> rotateHandler;
    std::function<void()> pressHandler;
};
