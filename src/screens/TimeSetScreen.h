#ifndef TimeSetScreen_h_
#define TimeSetScreen_h_

#include "BaseScreen.h"
#include <Arduino.h>

class TimeSetScreen: public BaseScreen
{
    public:
        TimeSetScreen(ScreensProvider *screensProvider);
        static BaseScreen *staticConstructor(ScreensProvider *screensProvider);
        BaseScreen::StaticConstructorPtr getPtrToStaticConstructor() override;
        void load(BaseScreen::StaticConstructorPtr fromScreen);

        BaseScreen::StaticConstructorPtr clickUpButton();
        BaseScreen::StaticConstructorPtr clickDownButton();
        BaseScreen::StaticConstructorPtr clickCancelButton();
        BaseScreen::StaticConstructorPtr clickOkButton();

    private:
        uint8_t _curPosition;
        uint8_t _curHours;
        uint8_t _curMinutes;
        uint8_t _curSeconds;
        uint8_t _curDate;
        uint8_t _curMonth;
        uint16_t _curYear;

        static uint8_t posToCursorPos(uint8_t pos);
        void drawCursor(uint8_t oldPos, uint8_t newPos);
};

#endif