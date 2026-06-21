#include <touch.h>

// static ISR shims, one per possible sensor (max 4)
static TouchSensor *slots[4] = {};

static void IRAM_ATTR isr0() { if (slots[0]) slots[0]->event = true; }
static void IRAM_ATTR isr1() { if (slots[1]) slots[1]->event = true; }
static void IRAM_ATTR isr2() { if (slots[2]) slots[2]->event = true; }
static void IRAM_ATTR isr3() { if (slots[3]) slots[3]->event = true; }

static void (*isrs[4])() = { isr0, isr1, isr2, isr3 };

bool TouchSensor::begin(uint8_t address, uint8_t irqPin, uint8_t touchThreshold, uint8_t releaseThreshold, TwoWire &wire) {
    if (!mpr.begin(address, &wire, touchThreshold, releaseThreshold, true)) return false;

    // Register in next free slot
    for (int i = 0; i < 4; i++) {
        if (slots[i] == nullptr) {
            slots[i] = this;
            pinMode(irqPin, INPUT_PULLUP);
            attachInterrupt(digitalPinToInterrupt(irqPin), isrs[i], FALLING);
            break;
        }
    }

    return true;
}

void TouchSensor::loop() {
    if (!event) return;
    event = false;

    uint16_t touched = mpr.touched();
    for (uint8_t i = 0; i < 12; i++) {
        bool isNow = touched & (1 << i);
        bool wasOn = lastTouched & (1 << i);

        if (isNow && !wasOn && touchHandler) touchHandler(i);
        if (!isNow && wasOn && releaseHandler) releaseHandler(i);
    }

    lastTouched = touched;
}