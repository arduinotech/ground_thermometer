#ifndef TempLogRecord_h_
#define TempLogRecord_h_

#include <Arduino.h>

struct TempLogRecord
{
    uint8_t date;
    uint8_t month;
    uint16_t year;
    uint8_t hour;

    int8_t tempSensor1;
    int8_t tempSensor2;
};

#endif