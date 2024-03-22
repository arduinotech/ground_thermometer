#include <Arduino.h>
#include <Streaming.h>
#include <microDS18B20.h>
#include "hardware/Config.h"
#include "ScreensProvider.h"
#include "Error.h"
#include "hardware/Storage.h"
#include "types/TempLogRecord.h"

MicroDS18B20<PIN_SENSOR_1> sensor1;
MicroDS18B20<PIN_SENSOR_2> sensor2;

ScreensProvider *screensProvider;

// void addTestDataToStorage()
// {
//     for (uint8_t i = 0; i <= 13; i++) {
//         TempLogRecord record;
//         record.hour = i;
//         record.date = 22;
//         record.month = 3;
//         record.year = 2024;
//         record.tempSensor1 = i - 5;
//         record.tempSensor2 = i - 3;
//         Storage::getInstance()->saveLogRecord(record);
//     }
// }

void setup()
{
    Serial.begin(115200);

    // Запустить 1 раз при замене платы Arduino
    // Storage::getInstance()->initMemory();

    // addTestDataToStorage();

    Controls *controls = new Controls();
    screensProvider = new ScreensProvider(controls);

    // delay(3000);
    // Storage::getInstance()->showDataToConsole();
}

void loop()
{
    static uint32_t tmr = 0;
    static int8_t lastSensor1Value;
    static int8_t lastSensor2Value;

    uint32_t now = millis();
    if (now < tmr) {
        tmr = 0;
    }

    if ((now - tmr) > 1000) {
        tmr = now;
        if (sensor1.readTemp()) {
            lastSensor1Value = round(sensor1.getTemp());
        } else {
            Error::throwError("Error sensor 1");
        }
        if (sensor2.readTemp()) {
            lastSensor2Value = round(sensor2.getTemp());
        } else {
            Error::throwError("Error sensor 2");
        }
        sensor1.requestTemp();
        sensor2.requestTemp();
    }

    screensProvider->tick(lastSensor1Value, lastSensor2Value);
}
