#include "ScreensProvider.h"
#include "screens/MainScreen.h"
#include "hardware/Rtc.h"
#include "hardware/Storage.h"
#include "types/TempLogRecord.h"

ScreensProvider::ScreensProvider(Controls *controls)
{
    _controls = controls;

    _currentScreen = new MainScreen(this);
    _currentScreen->load(NULL);

    _curHour = Rtc::getInstance()->getRtc()->getHours();
}

void ScreensProvider::tick(int8_t sensor1Value, int8_t sensor2Value)
{
    _sensor1LastValue = sensor1Value;
    _sensor2LastValue = sensor2Value;

    saveLogRecordIfNeed();

    _currentScreen->tick();

    _controls->tick();

    if (_controls->isUpButtonPressed()) {
        setCurrentScreen(_currentScreen->clickUpButton());
    }

    if (_controls->isDownButtonPressed()) {
        setCurrentScreen(_currentScreen->clickDownButton());
    }

    if (_controls->isCancelButtonPressed()) {
        setCurrentScreen(_currentScreen->clickCancelButton());
    }

    if (_controls->isOkButtonPressed()) {
        setCurrentScreen(_currentScreen->clickOkButton());
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

    Storage::getInstance()->saveLogRecord(record);
}
