#ifndef Storage_h_
#define Storage_h_

#include "types/TempLogRecord.h"
#include <Arduino.h>

/**
 * Размер EEPROM: 1000kb
 * В данный размер влезет 140 пакетов с типом TempLogRecord (7 байт на пакет), после чего начинаем
 * перезаписывать поверх старых, начиная с самого старого.
 *
 * Структура хранения данных в памяти в формате
 * адрес (смещение в байтах):размер данных (в байтах):назначение
 *
 * 0:2:"адрес для записи следующей структуры данных, инициализируем значением 20"
 * 2:1:"кол-во записанных структур данных, при достижении значения 140 фиксируется на этом значении, инициализируем 0"
 * 3:17:"резервируем для каких-то других данных, например, для настроек и тд"
 * 20:7:"1-ая структура"
 * 27:7:"2-ая структура"
 * ...
 * 993:7:"140-ая структура"
*/

// Адрес, по которому содержится значение сдвига для следующей структуры
#define NEW_LOG_RECORD_ADDRESS_OFFSET 0
// Адрес, по которому содержится текущее кол-во записанных структур, либо 140, если их 140 или больше (пошла перезапись)
#define LOG_RECORDS_COUNT_OFFSET 2
// Адрес первой структуры
#define LOG_RECORDS_FIRST_OFFSET 20
// Адрес последней структуры
#define LOG_RECORDS_LAST_OFFSET 993
// Размер структуры
#define LOG_RECORDS_SIZE 7
// Кол-во структур, помещающихся в память
#define LOG_RECORDS_ALL_COUNT 140


class Storage
{
    public:
        static Storage *getInstance();

        void initMemory();
        void saveLogRecord(TempLogRecord logRecord);
        void showDataToConsole();

        void getValues(
            uint16_t year,
            uint8_t month,
            uint8_t date,
            uint8_t hour,
            bool twoHoursFormat,
            uint8_t sensorNum,
            String *values
        );

    protected:
        Storage();

    private:
        static Storage *_instance;

};

#endif