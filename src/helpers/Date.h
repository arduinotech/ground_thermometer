#ifndef Date_h_
#define Date_h_

#include <Arduino.h>

class Date
{
    public:
        static uint8_t getNumOfDaysInMonth(uint16_t year, uint8_t month);
};

#endif