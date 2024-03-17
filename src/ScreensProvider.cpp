#include "ScreensProvider.h"
#include "screens/MainScreen.h"

ScreensProvider::ScreensProvider(Controls *controls)
{
    _controls = controls;

    _currentScreen = new MainScreen(this);
    _currentScreen->load(NULL);
}

void ScreensProvider::tick(int8_t sensor1Value, int8_t sensor2Value)
{
    _sensor1LastValue = sensor1Value;
    _sensor2LastValue = sensor2Value;

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
