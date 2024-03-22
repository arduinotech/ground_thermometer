#ifndef StringFormater_h_
#define StringFormater_h_

#include <Arduino.h>

class StringFormater
{
    public:
        static String formatByteNum(uint8_t num);
};

#endif