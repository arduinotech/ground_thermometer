#include "MainScreen.h"
#include "hardware/Display.h"
#include "hardware/Rtc.h"
#include "ScreensProvider.h"

MainScreen::MainScreen(ScreensProvider *screensProvider):
BaseScreen(screensProvider)
{
    _lastUpdateScreen = 0;
}

BaseScreen *MainScreen::staticConstructor(ScreensProvider *screensProvider)
{
    return new MainScreen(screensProvider);
}

BaseScreen::StaticConstructorPtr MainScreen::getPtrToStaticConstructor()
{
    return MainScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr MainScreen::tick()
{
    uint32_t now = millis();
    if (now < _lastUpdateScreen) {
        _lastUpdateScreen = 0;
        return MainScreen::staticConstructor;
    }

    if ((now - _lastUpdateScreen) > 1000) {
        _lastUpdateScreen = now;
        Display::getInstance()->clearScreen();
        Display::getInstance()->print(Rtc::getInstance()->getDateString().c_str(), 0, 0);
        Display::getInstance()->print(Rtc::getInstance()->getTimeString().c_str(), 0, 1);
        Display::getInstance()->print(String(_screensProvider->getLastSensor1Value()).c_str(), 0, 2);
        Display::getInstance()->print(String(_screensProvider->getLastSensor2Value()).c_str(), 0, 3);

    }

    return MainScreen::staticConstructor;
}

void MainScreen::load(BaseScreen::StaticConstructorPtr fromScreen)
{
    Display::getInstance()->clearScreen();
}

BaseScreen::StaticConstructorPtr MainScreen::clickUpButton()
{
    Display::getInstance()->print("clickUpButton", 0, 0);
    return MainScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr MainScreen::clickDownButton()
{
    Display::getInstance()->print("clickDownButton", 0, 0);
    return MainScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr MainScreen::clickCancelButton()
{
    Display::getInstance()->print("clickCancelButton", 0, 0);
    return MainScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr MainScreen::clickOkButton()
{
    Display::getInstance()->print("clickOkButton", 0, 0);
    return MainScreen::staticConstructor;
}
