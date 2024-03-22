#include "Storage.h"
#include <EEPROM.h>
#include <Streaming.h>
#include "helpers/Date.h"
#include "helpers/StringFormater.h"

Storage *Storage::_instance = NULL;

Storage *Storage::getInstance()
{
    if (NULL == _instance) {
        _instance = new Storage();
    }
    return _instance;
}

Storage::Storage()
{
}

void Storage::initMemory()
{
    EEPROM.put(NEW_LOG_RECORD_ADDRESS_OFFSET, LOG_RECORDS_FIRST_OFFSET);
    EEPROM.put(LOG_RECORDS_COUNT_OFFSET, 0);
}

void Storage::saveLogRecord(TempLogRecord logRecord)
{
    uint16_t newRecordOffset;
    EEPROM.get(NEW_LOG_RECORD_ADDRESS_OFFSET, newRecordOffset);

    uint8_t recordsCount;
    EEPROM.get(LOG_RECORDS_COUNT_OFFSET, recordsCount);

    EEPROM.put(newRecordOffset, logRecord);

    if (recordsCount < LOG_RECORDS_ALL_COUNT) {
        recordsCount++;
        EEPROM.put(LOG_RECORDS_COUNT_OFFSET, recordsCount);
    }

    if (LOG_RECORDS_LAST_OFFSET == newRecordOffset) {
        newRecordOffset = LOG_RECORDS_FIRST_OFFSET;
    } else {
        newRecordOffset += LOG_RECORDS_SIZE;
    }
    EEPROM.put(NEW_LOG_RECORD_ADDRESS_OFFSET, newRecordOffset);
}

void Storage::showDataToConsole()
{
    uint16_t newRecordOffset;
    EEPROM.get(NEW_LOG_RECORD_ADDRESS_OFFSET, newRecordOffset);

    uint8_t recordsCount;
    EEPROM.get(LOG_RECORDS_COUNT_OFFSET, recordsCount);

    Serial << "newRecordOffset: " << newRecordOffset << endl;
    Serial << "recordsCount: " << recordsCount << endl << endl;
    Serial << "Data:" << endl;

    Serial << "hour, date, month, year, sensor1, sensor2" << endl;
    uint16_t recordOffset = newRecordOffset;
    for (size_t i = 0; i < recordsCount; i++) {
        recordOffset -= LOG_RECORDS_SIZE;
        if (recordOffset < LOG_RECORDS_FIRST_OFFSET) {
            recordOffset = LOG_RECORDS_LAST_OFFSET;
        }
        TempLogRecord record;
        EEPROM.get(recordOffset, record);
        Serial << record.hour << ", " << record.date << ", " << record.month << ", " << record.year
                                << ", " << record.tempSensor1 << ", " << record.tempSensor2 << endl;
    }
}

void Storage::getValues(uint16_t year, uint8_t month, uint8_t date, uint8_t hour, bool twoHoursFormat, uint8_t sensorNum, String *values)
{
    for (uint8_t i = 0; i < 12; i++) {
        values[i] = "   ";
    }

    uint16_t curYear = year;
    uint8_t curMonth = month;
    uint8_t curDate = date;
    uint8_t curHour = hour;
    TempLogRecord needValuesDatesAndHours[12];

    for (uint8_t i = 0; i < 12; i++) {
        needValuesDatesAndHours[i].year = curYear;
        needValuesDatesAndHours[i].month = curMonth;
        needValuesDatesAndHours[i].date = curDate;
        needValuesDatesAndHours[i].hour = curHour;

        if (!twoHoursFormat && (curHour > 0)) {
            curHour--;
            continue;
        }
        if (twoHoursFormat && (curHour > 1)) {
            curHour -= 2;
            continue;
        }

        if (!twoHoursFormat) {
            curHour = 23;
        } else {
            curHour = 22;
        }

        if (curDate > 1) {
            curDate--;
            continue;
        }
        if (curMonth > 1) {
            curMonth--;
        } else {
            curMonth = 12;
            curYear--;
        }

        curDate = Date::getNumOfDaysInMonth(curYear, curMonth);
    }

    uint16_t newRecordOffset;
    EEPROM.get(NEW_LOG_RECORD_ADDRESS_OFFSET, newRecordOffset);

    uint8_t recordsCount;
    EEPROM.get(LOG_RECORDS_COUNT_OFFSET, recordsCount);

    uint16_t recordOffset = newRecordOffset;
    for (size_t i = 0; i < recordsCount; i++) {
        recordOffset -= LOG_RECORDS_SIZE;
        if (recordOffset < LOG_RECORDS_FIRST_OFFSET) {
            recordOffset = LOG_RECORDS_LAST_OFFSET;
        }
        TempLogRecord record;
        EEPROM.get(recordOffset, record);

        for (uint8_t i = 0; i < 12; i++) {
            if (
                record.year == needValuesDatesAndHours[i].year
                && record.month == needValuesDatesAndHours[i].month
                && record.date == needValuesDatesAndHours[i].date
                && record.hour == needValuesDatesAndHours[i].hour
            ) {
                if (sensorNum == 1) {
                    values[i] = StringFormater::formatForThreeSigns(record.tempSensor1);
                } else {
                    values[i] = StringFormater::formatForThreeSigns(record.tempSensor2);
                }
            }
        }
    }
}