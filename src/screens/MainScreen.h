#ifndef MainScreen_h_
#define MainScreen_h_

#include "BaseScreen.h"
#include <Arduino.h>

class MainScreen: public BaseScreen
{
    public:
        MainScreen(ScreensProvider *screensProvider);
        static BaseScreen *staticConstructor(ScreensProvider *screensProvider);
        BaseScreen::StaticConstructorPtr getPtrToStaticConstructor() override;
        void load(BaseScreen::StaticConstructorPtr fromScreen);

        BaseScreen::StaticConstructorPtr tick();
        BaseScreen::StaticConstructorPtr clickUpButton();
        BaseScreen::StaticConstructorPtr clickDownButton();
        BaseScreen::StaticConstructorPtr clickCancelButton();
        BaseScreen::StaticConstructorPtr clickOkButton();

    private:
        uint32_t _lastUpdateScreen;
};

#endif