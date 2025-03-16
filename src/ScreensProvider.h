#ifndef ScreensProvider_h_
#define ScreensProvider_h_

#include <Arduino.h>
#include "hardware/Controls.h"
#include "screens/BaseScreen.h"
#include "hardware/Config.h"

#define SCREEN_OFF_TIMEOUT_MILLIS 10000

extern volatile bool wakeUpByInterrupt;
extern volatile bool isSleeping;

class ScreensProvider
{
    public:
        ScreensProvider(Controls *controls);
        void tick(int8_t sensor1Value, int8_t sensor2Value);

        int8_t getLastSensor1Value() const;
        int8_t getLastSensor2Value() const;
        void setSensorNum(uint8_t sensorNum);
        uint8_t getSensorNum() const;
        void updateLastClickTime();
        void redrawCurrentScreen();


    private:
        Controls *_controls;
        BaseScreen *_currentScreen;
        int8_t _sensor1LastValue{};
        int8_t _sensor2LastValue{};
        uint8_t _sensorNum{};
        uint32_t _lastClickTime;

        void setCurrentScreen(BaseScreen::StaticConstructorPtr staticConstructorPtr);
};

#endif