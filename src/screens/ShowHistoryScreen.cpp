#include "ShowHistoryScreen.h"
#include "hardware/Display.h"
#include "hardware/Rtc.h"
#include "hardware/Storage.h"
#include "MainScreen.h"
#include "helpers/StringFormater.h"
#include "helpers/Date.h"
#include <Streaming.h>

ShowHistoryScreen::ShowHistoryScreen(ScreensProvider *screensProvider):
BaseScreen(screensProvider)
{
}

BaseScreen *ShowHistoryScreen::staticConstructor(ScreensProvider *screensProvider)
{
    return new ShowHistoryScreen(screensProvider);
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::getPtrToStaticConstructor()
{
    return ShowHistoryScreen::staticConstructor;
}

void ShowHistoryScreen::load(BaseScreen::StaticConstructorPtr fromScreen)
{
    _cursor = 0;
    _isSetting = false;
    _twoHoursFormat = false;

    Display::getInstance()->clearScreen();
    Display::getInstance()->print(String(_sensorNum), 0, 0);
    drawCursor(_cursor, _cursor);

    _curYear = Rtc::getInstance()->getRtc()->getYear();
    _curMonth = Rtc::getInstance()->getRtc()->getMonth();
    _curDate = Rtc::getInstance()->getRtc()->getDate();
    _curHour = Rtc::getInstance()->getRtc()->getHours();

    Display::getInstance()->print(StringFormater::formatByteNum(_curDate) + String(".") + StringFormater::formatByteNum(_curMonth), 2, 0);
    Display::getInstance()->print(StringFormater::formatByteNum(_curHour) + String(":00"), 2, 1);
    Display::getInstance()->print(_twoHoursFormat ? String("2h") : String("1h"), 2, 2);

    reloadValues();
}

void ShowHistoryScreen::setSensorNum(uint8_t sensorNum)
{
    _sensorNum = sensorNum;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickUpButton()
{
    if (!_isSetting && (_cursor > 0)) {
        _cursor--;
        drawCursor(_cursor + 1, _cursor);
    }
    if (_isSetting && (0 == _cursor)) {
        if (_curDate > 1) {
            _curDate--;
        } else {
            if (_curMonth > 1) {
                _curMonth--;
            } else {
                _curMonth = 12;
                _curYear--;
            }
            _curDate = Date::getNumOfDaysInMonth(_curYear, _curMonth);
        }
        Display::getInstance()->print(StringFormater::formatByteNum(_curDate) + String(".") + StringFormater::formatByteNum(_curMonth), 2, 0);
        reloadValues();
    }
    if (_isSetting && (1 == _cursor)) {
        if (_curHour > 0) {
            _curHour--;
            Display::getInstance()->print(StringFormater::formatByteNum(_curHour) + String(":00"), 2, 1);
            reloadValues();
        } else {
            _curHour = 23;
            if (_curDate > 1) {
                _curDate--;
            } else {
                if (_curMonth > 1) {
                    _curMonth--;
                } else {
                    _curMonth = 12;
                    _curYear--;
                }
                _curDate = Date::getNumOfDaysInMonth(_curYear, _curMonth);
            }
            Display::getInstance()->print(StringFormater::formatByteNum(_curDate) + String(".") + StringFormater::formatByteNum(_curMonth), 2, 0);
            Display::getInstance()->print(StringFormater::formatByteNum(_curHour) + String(":00"), 2, 1);
            reloadValues();
        }
    }
    if (_isSetting && (2 == _cursor)) {
        _twoHoursFormat = !_twoHoursFormat;
        Display::getInstance()->print(_twoHoursFormat ? String("2h") : String("1h"), 2, 2);
        reloadValues();
    }
    return ShowHistoryScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickDownButton()
{
    if (!_isSetting && (_cursor < 2)) {
        _cursor++;
        drawCursor(_cursor - 1, _cursor);
    }
    if (_isSetting && (0 == _cursor)) {
        if (_curDate < Date::getNumOfDaysInMonth(_curYear, _curMonth)) {
            _curDate++;
        } else {
            _curDate = 1;
            if (_curMonth < 12) {
                _curMonth++;
            } else {
                _curMonth = 1;
                _curYear++;
            }
        }
        Display::getInstance()->print(StringFormater::formatByteNum(_curDate) + String(".") + StringFormater::formatByteNum(_curMonth), 2, 0);
        reloadValues();
    }
    if (_isSetting && (1 == _cursor)) {
        if (_curHour < 23) {
            _curHour++;
            Display::getInstance()->print(StringFormater::formatByteNum(_curHour) + String(":00"), 2, 1);
            reloadValues();
        } else {
            _curHour = 0;
            if (_curDate < Date::getNumOfDaysInMonth(_curYear, _curMonth)) {
                _curDate++;
            } else {
                _curDate = 1;
                if (_curMonth < 12) {
                    _curMonth++;
                } else {
                    _curMonth = 1;
                    _curYear++;
                }
            }
            Display::getInstance()->print(StringFormater::formatByteNum(_curDate) + String(".") + StringFormater::formatByteNum(_curMonth), 2, 0);
            Display::getInstance()->print(StringFormater::formatByteNum(_curHour) + String(":00"), 2, 1);
            reloadValues();
        }
    }
    if (_isSetting && (2 == _cursor)) {
        _twoHoursFormat = !_twoHoursFormat;
        Display::getInstance()->print(_twoHoursFormat ? String("2h") : String("1h"), 2, 2);
        reloadValues();
    }
    return ShowHistoryScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickCancelButton()
{
    if (!_isSetting) {
        return MainScreen::staticConstructor;
    } else {
        _isSetting = false;
    }
    return ShowHistoryScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickOkButton()
{
    _isSetting = !_isSetting;
    return ShowHistoryScreen::staticConstructor;
}

void ShowHistoryScreen::drawCursor(uint8_t oldPos, uint8_t newPos)
{
    if (oldPos != newPos) {
        Display::getInstance()->print("  ", 0, oldPos);
    }
    Display::getInstance()->print("->", 0, newPos);
}

void ShowHistoryScreen::reloadValues()
{
    String values[12];
    Storage::getInstance()->getValues(_curYear, _curMonth, _curDate, _curHour, _twoHoursFormat, _sensorNum, values);

    uint8_t curX = 8;
    uint8_t curY = 0;
    for (uint8_t i = 0; i < 12; i++) {
        Serial << "curX = " << curX << ", curY = " << curY << ", value = " << values[i] << ", length = " << values[i].length() << endl;
        Display::getInstance()->print(values[i], curX, curY);
        if (curY < 3) {
            curY++;
        } else {
            curY = 0;
            curX += 4;
        }
    }
}
