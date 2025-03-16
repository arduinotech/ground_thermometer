#include <Arduino.h>
#include <Streaming.h>
#include <GyverDS18.h>
#include <GyverPower.h>

#include "hardware/Config.h"
#include "ScreensProvider.h"
#include "hardware/Storage.h"
#include "types/TempLogRecord.h"
#include "hardware/Rtc.h"
#include "hardware/Display.h"

GyverDS18Single sensor1(PIN_SENSOR_1, false);
GyverDS18Single sensor2(PIN_SENSOR_2, false);

ScreensProvider *screensProvider;
int8_t curHour;

int8_t sensor1Value = 0;
int8_t sensor2Value = 0;

volatile bool wakeUpByInterrupt = true;
volatile bool firstLoopProcessAfterWakeUpByInterrupt = true;
volatile bool isSleeping = false;

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

void wakeup()
{
    if (isSleeping) {
        wakeUpByInterrupt = true;
        firstLoopProcessAfterWakeUpByInterrupt = true;
        power.wakeUp();
        isSleeping = false;
    }
}

void updateTempValues()
{
    sensor1.requestTemp();
    sensor2.requestTemp();

    while (!sensor1.ready()) {}
    while (!sensor2.ready()) {}

    if (sensor1.readTemp()) {
        sensor1Value = round(sensor1.getTemp());
    } else {
        sensor1Value = 0;
    }

    if (sensor2.readTemp()) {
        sensor2Value = round(sensor2.getTemp());
    } else {
        sensor2Value = 0;
    }
}

void setup()
{
//    Serial.begin(115200);

    pinMode(PIN_POWER_SENSORS, OUTPUT);
    pinMode(PIN_POWER_RTC, OUTPUT);
    pinMode(PIN_POWER_DISPLAY, OUTPUT);

    digitalWrite(PIN_POWER_SENSORS, HIGH);
    digitalWrite(PIN_POWER_RTC, HIGH);
    digitalWrite(PIN_POWER_DISPLAY, HIGH);

    delay(500);

    Rtc::getInstance()->getRtc()->begin();

    // Rtc::getInstance()->getRtc()->setTime(0, 05, 22, 15, 3, 2025);

    // Запустить 1 раз при замене платы Arduino
//     Storage::getInstance()->initMemory();

    // addTestDataToStorage();

    curHour = 0;

    Controls *controls = new Controls();
    screensProvider = new ScreensProvider(controls);

    // Storage::getInstance()->showDataToConsole();

    power.calibrate(8000);
    power.setSleepMode(POWERDOWN_SLEEP);

    attachInterrupt(0, wakeup, FALLING);
}

void loop()
{
    static uint32_t lastTempUpdate = 0;

    if (!wakeUpByInterrupt) {
        digitalWrite(PIN_POWER_RTC, HIGH);
        delay(500);

        Rtc::getInstance()->getRtc()->begin();

        int8_t newHour = Rtc::getInstance()->getRtc()->getHours();

        if (newHour != curHour) {
            curHour = newHour;

            digitalWrite(PIN_POWER_SENSORS, HIGH);

            updateTempValues();

            TempLogRecord record;
            record.hour = curHour;
            record.date = Rtc::getInstance()->getRtc()->getDate();
            record.month = Rtc::getInstance()->getRtc()->getMonth();
            record.year = Rtc::getInstance()->getRtc()->getYear();
            record.tempSensor1 = sensor1Value;
            record.tempSensor2 = sensor2Value;

            Storage::getInstance()->saveLogRecord(record);
        }

        digitalWrite(PIN_POWER_SENSORS, LOW);
        digitalWrite(PIN_POWER_RTC, LOW);

        delay(500);

        isSleeping = true;
        power.sleepDelay(1800000); // Просыпаемся раз в 30 мин
    } else {
        if (firstLoopProcessAfterWakeUpByInterrupt) {
            digitalWrite(PIN_POWER_RTC, HIGH);
            digitalWrite(PIN_POWER_SENSORS, HIGH);

            delay(500);

            Rtc::getInstance()->getRtc()->begin();

            Display::getInstance()->turnOnDisplay();
            delay(500);

            screensProvider->updateLastClickTime();
            screensProvider->redrawCurrentScreen();

            updateTempValues();

            sensor1.requestTemp();
            sensor2.requestTemp();

            firstLoopProcessAfterWakeUpByInterrupt = false;
        } else {
            uint32_t now = millis();
            if (lastTempUpdate > now) {
                lastTempUpdate = 0;
            }

            if ((now - lastTempUpdate) > 1000) {
                lastTempUpdate = now;

                if (sensor1.ready()) {
                    if (sensor1.readTemp()) {
                        sensor1Value = round(sensor1.getTemp());
                    } else {
                        sensor1Value = 0;
                    }
                    sensor1.requestTemp();
                }

                if (sensor2.ready()) {
                    if (sensor2.readTemp()) {
                        sensor2Value = round(sensor2.getTemp());
                    } else {
                        sensor2Value = 0;
                    }
                    sensor2.requestTemp();
                }
            }

            screensProvider->tick(sensor1Value, sensor2Value);
        }
    }
}
