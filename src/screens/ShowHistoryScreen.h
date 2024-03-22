#ifndef ShowHistoryScreen_h_
#define ShowHistoryScreen_h_

#include "BaseScreen.h"
#include <Arduino.h>

class ShowHistoryScreen: public BaseScreen
{
    public:
        ShowHistoryScreen(ScreensProvider *screensProvider);
        static BaseScreen *staticConstructor(ScreensProvider *screensProvider);
        BaseScreen::StaticConstructorPtr getPtrToStaticConstructor() override;
        void load(BaseScreen::StaticConstructorPtr fromScreen);

        void setSensorNum(uint8_t sensorNum);

        BaseScreen::StaticConstructorPtr clickUpButton();
        BaseScreen::StaticConstructorPtr clickDownButton();
        BaseScreen::StaticConstructorPtr clickCancelButton();
        BaseScreen::StaticConstructorPtr clickOkButton();

    private:
        uint8_t _sensorNum;
        uint8_t _cursor;
        void drawCursor(uint8_t oldPos, uint8_t newPos);
        bool _isSetting;
        uint16_t _curYear;
        uint8_t _curDate;
        uint8_t _curMonth;
        uint8_t _curHour;
        uint8_t _twoHoursFormat;
        void reloadValues();
};

#endif