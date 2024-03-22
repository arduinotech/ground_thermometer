#ifndef ScreensProvider_h_
#define ScreensProvider_h_

#include <Arduino.h>
#include "hardware/Controls.h"
#include "screens/BaseScreen.h"
#include "hardware/Config.h"

class ScreensProvider
{
    public:
        ScreensProvider(Controls *controls);
        void tick(int8_t sensor1Value, int8_t sensor2Value);

        int8_t getLastSensor1Value();
        int8_t getLastSensor2Value();

    private:
        Controls *_controls;
        BaseScreen *_currentScreen;
        int8_t _sensor1LastValue;
        int8_t _sensor2LastValue;
        int8_t _curHour;

        void setCurrentScreen(BaseScreen::StaticConstructorPtr staticConstructorPtr);
        void saveLogRecordIfNeed();
};

#endif