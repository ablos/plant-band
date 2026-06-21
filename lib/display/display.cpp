#include <display.h>

Display::Display(uint8_t rs, uint8_t e, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
    : lcd(rs, e, d4, d5, d6, d7) {}

void Display::begin() {
    lcd.begin(16, 2);
}

void Display::setCursor(uint8_t x, uint8_t y) {
    lcd.setCursor(x, y);
}

void Display::print(const char* value) {
    lcd.print(value);
}

void Display::println(const char* value) {
    clear();

    // Print value if less than or equal 16
    if (strlen(value) <= 16) {
        lcd.print(value);
    }
    
    // Wrap to next line if longer
    else if (strlen(value) <= 32) {
        lcd.print(value);
        lcd.setCursor(0, 1);
        lcd.print(value + 16);
    }
    
    // Wrap and omit last characters with dots
    else {
        char buf[17];
        strncpy(buf, value, 16);
        buf[16] = '\0';
        lcd.print(buf);
        lcd.setCursor(0, 1);
        strncpy(buf, value + 16, 13);
        buf[13] = '\0';
        lcd.print(buf);
        lcd.print("...");
    }
}

void Display::clear() {
    // Clear screen
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 0);
}