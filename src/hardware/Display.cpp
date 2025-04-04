#include <Arduino.h>

#include "Display.h"
#include "Config.h"

Display *Display::_instance = NULL;

Display *Display::getInstance()
{
    if (NULL == _instance) {
        _instance = new Display();
    }
    return _instance;
}

Display::Display()
{
    _lcd = new LiquidCrystal_I2C(LCD_ADDR, LCD_COLS, LCD_ROWS);
    _lcd->init();
    _lcd->backlight();
    _lcd->clear();
}

void Display::turnOffDisplay()
{
    _lcd->noBacklight();
    _lcd->noDisplay();
//    digitalWrite(PIN_POWER_DISPLAY, LOW);
}

void Display::turnOnDisplay()
{
//    digitalWrite(PIN_POWER_DISPLAY, HIGH);
//    _lcd->init();
    _lcd->display();
    _lcd->backlight();
    _lcd->clear();
}

void Display::clearScreen()
{
    _lcd->clear();
}

void Display::print(const char *text, uint8_t x, uint8_t y)
{
    _lcd->setCursor(x, y);
    _lcd->print(text);
}

void Display::print(String text, uint8_t x, uint8_t y)
{
    _lcd->setCursor(x, y);
    _lcd->print(text.c_str());
}

void Display::error(const char *text)
{
    clearScreen();
    print("ERROR!!!", 7, 0);
    print(text, 0, 2);
}
