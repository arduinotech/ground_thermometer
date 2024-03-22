#include "ShowHistoryScreen.h"
#include "hardware/Display.h"
#include "MainScreen.h"

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
    Display::getInstance()->clearScreen();
    Display::getInstance()->print(String(_sensorNum), 0, 0);
}

void ShowHistoryScreen::setSensorNum(uint8_t sensorNum)
{
    _sensorNum = sensorNum;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickUpButton()
{
    return ShowHistoryScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickDownButton()
{
    return ShowHistoryScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickCancelButton()
{
    return MainScreen::staticConstructor;
}

BaseScreen::StaticConstructorPtr ShowHistoryScreen::clickOkButton()
{
    return ShowHistoryScreen::staticConstructor;
}
