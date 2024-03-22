#include "Storage.h"
#include <EEPROM.h>
#include <Streaming.h>

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
