#include "ShowHistoryScreen.h"
#include "hardware/Display.h"
#include "hardware/Rtc.h"
#include "MainScreen.h"
#include "helpers/StringFormater.h"

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
    _oneHoursFormat = true;

    Display::getInstance()->clearScreen();
    Display::getInstance()->print(String(_sensorNum), 0, 0);
    drawCursor(_cursor, _cursor);

    _curYear = Rtc::getInstance()->getRtc()->getYear();
    _curMonth = Rtc::getInstance()->getRtc()->getMonth();
    _curDate = Rtc::getInstance()->getRtc()->getDate();
    _curHour = Rtc::getInstance()->getRtc()->getHours();

    Display::getInstance()->print(StringFormater::formatByteNum(_curDate) + String(".") + StringFormater::formatByteNum(_curMonth), 2, 0);
    Display::getInstance()->print(StringFormater::formatByteNum(_curHour) + String(":00"), 2, 1);
    Display::getInstance()->print(_oneHoursFormat ? String("1h") : String("2h"), 2, 2);
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
    return ShowHistoryScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickDownButton()
{
    if (!_isSetting && (_cursor < 2)) {
        _cursor++;
        drawCursor(_cursor - 1, _cursor);
    }
    return ShowHistoryScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickCancelButton()
{
    if (!_isSetting) {
        return MainScreen::staticConstructor;
    }
    return ShowHistoryScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickOkButton()
{
    return ShowHistoryScreen::staticConstructor;
}

void ShowHistoryScreen::drawCursor(uint8_t oldPos, uint8_t newPos)
{
    if (oldPos != newPos) {
        Display::getInstance()->print("  ", 0, oldPos);
    }
    Display::getInstance()->print("->", 0, newPos);
}
