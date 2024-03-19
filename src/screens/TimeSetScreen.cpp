#include "TimeSetScreen.h"
#include "hardware/Display.h"
#include "hardware/Rtc.h"
#include "ScreensProvider.h"
#include "MainScreen.h"

TimeSetScreen::TimeSetScreen(ScreensProvider *screensProvider):
BaseScreen(screensProvider)
{
}

BaseScreen *TimeSetScreen::staticConstructor(ScreensProvider *screensProvider)
{
    return new TimeSetScreen(screensProvider);
}

BaseScreen::StaticConstructorPtr TimeSetScreen::getPtrToStaticConstructor()
{
    return TimeSetScreen::staticConstructor;
}

void TimeSetScreen::load(BaseScreen::StaticConstructorPtr fromScreen)
{
    Display::getInstance()->clearScreen();

    _curPosition = 0;

    _curHours = Rtc::getInstance()->getRtc()->getHours();
    _curMinutes = Rtc::getInstance()->getRtc()->getMinutes();
    _curSeconds = Rtc::getInstance()->getRtc()->getSeconds();

    _curDate = Rtc::getInstance()->getRtc()->getDate();
    _curMonth = Rtc::getInstance()->getRtc()->getMonth();
    _curYear = Rtc::getInstance()->getRtc()->getYear();

    Display::getInstance()->print(TimeSetScreen::formatByteNum(_curHours), TimeSetScreen::posToCursorPos(0), 1);
    Display::getInstance()->print(String(":"), TimeSetScreen::posToCursorPos(0) + 2, 1);
    Display::getInstance()->print(TimeSetScreen::formatByteNum(_curMinutes), TimeSetScreen::posToCursorPos(1), 1);
    Display::getInstance()->print(String(":"), TimeSetScreen::posToCursorPos(1) + 2, 1);
    Display::getInstance()->print(TimeSetScreen::formatByteNum(_curSeconds), TimeSetScreen::posToCursorPos(2), 1);

    Display::getInstance()->print(TimeSetScreen::formatByteNum(_curDate), TimeSetScreen::posToCursorPos(3), 1);
    Display::getInstance()->print(String("-"), TimeSetScreen::posToCursorPos(3) + 2, 1);
    Display::getInstance()->print(TimeSetScreen::formatByteNum(_curMonth), TimeSetScreen::posToCursorPos(4), 1);
    Display::getInstance()->print(String("-"), TimeSetScreen::posToCursorPos(4) + 2, 1);
    Display::getInstance()->print(String(_curYear), TimeSetScreen::posToCursorPos(5), 1);

    drawCursor(_curPosition, _curPosition);
}

BaseScreen::StaticConstructorPtr TimeSetScreen::clickUpButton()
{
    if (0 == _curPosition) {
        if (_curHours > 0) {
            _curHours--;
        } else {
            _curHours = 23;
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curHours), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else if (1 == _curPosition) {
        if (_curMinutes > 0) {
            _curMinutes--;
        } else {
            _curMinutes = 59;
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curMinutes), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else if (2 == _curPosition) {
        if (_curSeconds > 0) {
            _curSeconds--;
        } else {
            _curSeconds = 59;
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curSeconds), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else if (3 == _curPosition) {
        if (_curDate > 0) {
            _curDate--;
        } else {
            _curDate = TimeSetScreen::getNumOfDaysInMonth(_curYear, _curMonth);
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curDate), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else if (4 == _curPosition) {
        if (_curMonth > 0) {
            _curMonth--;
        } else {
            _curMonth = 12;
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curMonth), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else { // 5
        _curYear--;
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curYear), TimeSetScreen::posToCursorPos(_curPosition), 1);
    }

    return TimeSetScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr TimeSetScreen::clickDownButton()
{
    if (0 == _curPosition) {
        if (_curHours < 23) {
            _curHours++;
        } else {
            _curHours = 0;
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curHours), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else if (1 == _curPosition) {
        if (_curMinutes < 59) {
            _curMinutes++;
        } else {
            _curMinutes = 0;
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curMinutes), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else if (2 == _curPosition) {
        if (_curSeconds < 59) {
            _curSeconds++;
        } else {
            _curSeconds = 0;
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curSeconds), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else if (3 == _curPosition) {
        if (_curDate < TimeSetScreen::getNumOfDaysInMonth(_curYear, _curMonth)) {
            _curDate++;
        } else {
            _curDate = 1;
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curDate), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else if (4 == _curPosition) {
        if (_curMonth < 12) {
            _curMonth++;
        } else {
            _curMonth = 1;
        }
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curMonth), TimeSetScreen::posToCursorPos(_curPosition), 1);
    } else { // 5
        _curYear++;
        Display::getInstance()->print(TimeSetScreen::formatByteNum(_curYear), TimeSetScreen::posToCursorPos(_curPosition), 1);
    }

    return TimeSetScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr TimeSetScreen::clickCancelButton()
{
    return MainScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr TimeSetScreen::clickOkButton()
{

    return TimeSetScreen::staticConstructor;
}

uint8_t TimeSetScreen::getNumOfDaysInMonth(uint16_t year, uint8_t month)
{
	if (month == 2) {
		if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
			return 29;
        }
		return 28;
	}

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		return 31;
    }
    return 30;
}

String TimeSetScreen::formatByteNum(uint8_t num)
{
    if (num < 10) {
        return String("0") + String(num);
    } else {
        return String(num);
    }
}

uint8_t TimeSetScreen::posToCursorPos(uint8_t pos)
{
    return pos * 3 + 1;
}

void TimeSetScreen::drawCursor(uint8_t oldPos, uint8_t newPos)
{
    uint8_t cursorOldPos = TimeSetScreen::posToCursorPos(oldPos);
    uint8_t cursorNewPos = TimeSetScreen::posToCursorPos(newPos);
    if (oldPos != newPos) {
        Display::getInstance()->print(" ", cursorOldPos, 2);
        Display::getInstance()->print(" ", cursorOldPos, 3);
    }
    Display::getInstance()->print("^", cursorNewPos, 2);
    Display::getInstance()->print("|", cursorNewPos, 3);
}
