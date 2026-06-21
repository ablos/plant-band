#include <knob.h>

bool Knob::begin(uint8_t aPin, uint8_t bPin, uint8_t btnPin) {
    encoder.attachHalfQuad(aPin, bPin);
    encoder.setCount(0);
    button = Button2(btnPin);
    button.setClickHandler([this](Button2&) {
        if (pressHandler) pressHandler();
    });
    return true;
}

void Knob::loop() {
    long count = encoder.getCount();
    if (count != lastCount) {
        if (rotateHandler) rotateHandler((int)(count - lastCount));
        lastCount = count;
    }
    button.loop();
}
