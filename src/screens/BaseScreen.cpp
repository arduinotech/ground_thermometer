#include "BaseScreen.h"
#include "ScreensProvider.h"
#include "Error.h"

BaseScreen::BaseScreen(ScreensProvider *screensProvider)
{
    _screensProvider = screensProvider;
}

BaseScreen *BaseScreen::staticConstructor(ScreensProvider *screensProvider)
{
    Error::throwError("Call virtual BaseScreen::staticConstructor()");
    return NULL;
}

BaseScreen::~BaseScreen()
{
    Serial.println("BaseScreen::~BaseScreen()");
}

BaseScreen::StaticConstructorPtr BaseScreen::getPtrToStaticConstructor()
{
    Error::throwError("Call virtual BaseScreen::getPtrToStaticConstructor()");
    return NULL;
}

void BaseScreen::load(BaseScreen::StaticConstructorPtr fromScreen)
{
    Error::throwError("Call virtual BaseScreen::load()");
}

BaseScreen::StaticConstructorPtr BaseScreen::tick()
{
    return getPtrToStaticConstructor();
}

BaseScreen::StaticConstructorPtr BaseScreen::clickUpButton()
{
    return getPtrToStaticConstructor();
}

BaseScreen::StaticConstructorPtr BaseScreen::clickDownButton()
{
    return getPtrToStaticConstructor();
}

BaseScreen::StaticConstructorPtr BaseScreen::clickCancelButton()
{
    return getPtrToStaticConstructor();
}

BaseScreen::StaticConstructorPtr BaseScreen::clickOkButton()
{
    return getPtrToStaticConstructor();
}
