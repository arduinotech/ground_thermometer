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
};

#endif