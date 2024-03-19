#include "MainScreen.h"
#include "hardware/Display.h"
#include "hardware/Rtc.h"
#include "ScreensProvider.h"
#include "TimeSetScreen.h"

MainScreen::MainScreen(ScreensProvider *screensProvider):
BaseScreen(screensProvider)
{
    _lastUpdateScreen = 0;
    _lastDate = "";
    _lastTime = "";
    _lastSensor1Value = 0;
    _lastSensor2Value = 0;
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

        String date = Rtc::getInstance()->getRtc()->getDateString();
        if (date != _lastDate) {
            _lastDate = date;
            Display::getInstance()->print(date.c_str(), 2, 0);
        }

        String time = Rtc::getInstance()->getRtc()->getTimeString();
        if (time != _lastTime) {
            _lastTime = time;
            Display::getInstance()->print(time.c_str(), 2, 1);
        }

        int8_t sensorValue1 = _screensProvider->getLastSensor1Value();
        if (sensorValue1 != _lastSensor1Value) {
            _lastSensor1Value = sensorValue1;
            Display::getInstance()->print(String("   ").c_str(), 2, 2);
            Display::getInstance()->print(String(sensorValue1).c_str(), 2, 2);
        }

        int8_t sensorValue2 = _screensProvider->getLastSensor2Value();
        if (sensorValue2 != _lastSensor2Value) {
            _lastSensor2Value = sensorValue2;
            Display::getInstance()->print(String("   ").c_str(), 2, 3);
            Display::getInstance()->print(String(sensorValue2).c_str(), 2, 3);
        }
    }

    return MainScreen::staticConstructor;
}

void MainScreen::load(BaseScreen::StaticConstructorPtr fromScreen)
{
    Display::getInstance()->clearScreen();
    if (TimeSetScreen::staticConstructor == fromScreen) {
        _curMenuItem = 0;
    } else {
        _curMenuItem = 0;
    }

    Display::getInstance()->print(String("->").c_str(), 0, _curMenuItem + 1);
}

BaseScreen::StaticConstructorPtr MainScreen::clickUpButton()
{
    if (_curMenuItem > 0) {
        Display::getInstance()->print(String("  ").c_str(), 0, _curMenuItem + 1);
        _curMenuItem--;
        Display::getInstance()->print(String("->").c_str(), 0, _curMenuItem + 1);
    }
    return MainScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr MainScreen::clickDownButton()
{
    if (_curMenuItem < 2) {
        Display::getInstance()->print(String("  ").c_str(), 0, _curMenuItem + 1);
        _curMenuItem++;
        Display::getInstance()->print(String("->").c_str(), 0, _curMenuItem + 1);
    }
    return MainScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr MainScreen::clickCancelButton()
{
    return MainScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr MainScreen::clickOkButton()
{
    if (0 == _curMenuItem) {
        return TimeSetScreen::staticConstructor;
    }
    return MainScreen::staticConstructor;
}
