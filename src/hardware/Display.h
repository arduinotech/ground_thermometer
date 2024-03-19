#ifndef Display_h_
#define Display_h_

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Display
{
    public:
        static Display *getInstance();
        void clearScreen();
        void print(const char *text, uint8_t x, uint8_t y);
        void print(String text, uint8_t x, uint8_t y);
        void error(const char *text);

    protected:
        Display();

    private:
        static Display *_instance;
        LiquidCrystal_I2C *_lcd;
};

#endif