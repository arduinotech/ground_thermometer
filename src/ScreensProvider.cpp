#include "ScreensProvider.h"
#include "screens/MainScreen.h"
#include "hardware/Rtc.h"
#include "hardware/Display.h"
#include "hardware/Storage.h"
#include "types/TempLogRecord.h"
#include "screens/ShowHistoryScreen.h"

ScreensProvider::ScreensProvider(Controls *controls)
{
    _controls = controls;

    _currentScreen = new MainScreen(this);
    _currentScreen->load(NULL);

    _curHour = Rtc::getInstance()->getRtc()->getHours();

    _displayBacklight = true;
    _lastClickTime = millis();
}

void ScreensProvider::tick(int8_t sensor1Value, int8_t sensor2Value)
{
    uint32_t now = millis();

    _sensor1LastValue = sensor1Value;
    _sensor2LastValue = sensor2Value;

    saveLogRecordIfNeed();

    _currentScreen->tick();

    _controls->tick();

    if (_controls->isUpButtonPressed()) {
        if (!_displayBacklight) {
            _displayBacklight = true;
            Display::getInstance()->backlight();
        } else {
            setCurrentScreen(_currentScreen->clickUpButton());
        }
        _lastClickTime = now;
    }

    if (_controls->isDownButtonPressed()) {
        if (!_displayBacklight) {
            _displayBacklight = true;
            Display::getInstance()->backlight();
        } else {
            setCurrentScreen(_currentScreen->clickDownButton());
        }
        _lastClickTime = now;
    }

    if (_controls->isCancelButtonPressed()) {
        if (!_displayBacklight) {
            _displayBacklight = true;
            Display::getInstance()->backlight();
        } else {
            setCurrentScreen(_currentScreen->clickCancelButton());
        }
        _lastClickTime = now;
    }

    if (_controls->isOkButtonPressed()) {
        if (!_displayBacklight) {
            _displayBacklight = true;
            Display::getInstance()->backlight();
        } else {
            setCurrentScreen(_currentScreen->clickOkButton());
        }
        _lastClickTime = now;
    }

    if (((now - _lastClickTime) > SCREEN_OFF_TIMEOUT_MILLIS) && _displayBacklight) {
        Display::getInstance()->noBacklight();
        _displayBacklight = false;
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

int8_t ScreensProvider::getLastSensor1Value()
{
    return _sensor1LastValue;
}

int8_t ScreensProvider::getLastSensor2Value()
{
    return _sensor2LastValue;
}

void ScreensProvider::saveLogRecordIfNeed()
{
    uint8_t newHour = Rtc::getInstance()->getRtc()->getHours();
    if (newHour == _curHour) {
        return;
    }

    _curHour = newHour;
    TempLogRecord record;
    record.hour = _curHour;
    record.date = Rtc::getInstance()->getRtc()->getDate();
    record.month = Rtc::getInstance()->getRtc()->getMonth();
    record.year = Rtc::getInstance()->getRtc()->getYear();
    record.tempSensor1 = _sensor1LastValue;
    record.tempSensor2 = _sensor2LastValue;

    Storage::getInstance()->saveLogRecord(record);
}

void ScreensProvider::setSensorNum(uint8_t sensorNum)
{
    _sensorNum = sensorNum;
}

uint8_t ScreensProvider::getSensorNum()
{
    return _sensorNum;
}
