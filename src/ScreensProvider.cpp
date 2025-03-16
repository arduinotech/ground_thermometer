#include <GyverPower.h>
#include <Streaming.h>

#include "ScreensProvider.h"
#include "screens/MainScreen.h"
#include "hardware/Display.h"
#include "screens/ShowHistoryScreen.h"

ScreensProvider::ScreensProvider(Controls *controls)
{
    _controls = controls;

    _currentScreen = new MainScreen(this);
    _currentScreen->load(nullptr);

    _lastClickTime = millis();
}

void ScreensProvider::tick(int8_t sensor1Value, int8_t sensor2Value)
{
    uint32_t now = millis();

    _sensor1LastValue = sensor1Value;
    _sensor2LastValue = sensor2Value;

    _currentScreen->tick();

    _controls->tick();

    if (_controls->isUpButtonPressed()) {
        setCurrentScreen(_currentScreen->clickUpButton());
        _lastClickTime = now;
    }

    if (_controls->isDownButtonPressed()) {
        setCurrentScreen(_currentScreen->clickDownButton());
        _lastClickTime = now;
    }

    if (_controls->isCancelButtonPressed()) {
        setCurrentScreen(_currentScreen->clickCancelButton());
        _lastClickTime = now;
    }

    if (_controls->isOkButtonPressed()) {
        setCurrentScreen(_currentScreen->clickOkButton());
        _lastClickTime = now;
    }

    if (((now - _lastClickTime) > SCREEN_OFF_TIMEOUT_MILLIS)) {
        Display::getInstance()->turnOffDisplay();

        digitalWrite(PIN_POWER_SENSORS, LOW);
        digitalWrite(PIN_POWER_RTC, LOW);

        delay(500);
        wakeUpByInterrupt = false;
        isSleeping = true;
        power.sleepDelay(1800000); // Просыпаемся раз в 30 мин
    }
}

void ScreensProvider::setCurrentScreen(BaseScreen::StaticConstructorPtr staticConstructorPtr)
{
    if (staticConstructorPtr == _currentScreen->getPtrToStaticConstructor()) {
        return;
    }

    BaseScreen *newScreen = (*staticConstructorPtr)(this);
    BaseScreen::StaticConstructorPtr fromScreen = _currentScreen->getPtrToStaticConstructor();
    delete _currentScreen;
    if (ShowHistoryScreen::staticConstructor == staticConstructorPtr) {
        ((ShowHistoryScreen*)newScreen)->setSensorNum(_sensorNum);
    }
    newScreen->load(fromScreen);
    _currentScreen = newScreen;
}

int8_t ScreensProvider::getLastSensor1Value() const
{
    return _sensor1LastValue;
}

int8_t ScreensProvider::getLastSensor2Value() const
{
    return _sensor2LastValue;
}

void ScreensProvider::setSensorNum(uint8_t sensorNum)
{
    _sensorNum = sensorNum;
}

uint8_t ScreensProvider::getSensorNum() const
{
    return _sensorNum;
}

void ScreensProvider::updateLastClickTime()
{
    _lastClickTime = millis();
}

void ScreensProvider::redrawCurrentScreen()
{
    if (_currentScreen->getPtrToStaticConstructor() != MainScreen::staticConstructor) {
        setCurrentScreen(MainScreen::staticConstructor);
    } else {
        _currentScreen->redraw();
    }
}
