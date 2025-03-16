#ifndef BaseScreen_h_
#define BaseScreen_h_

class ScreensProvider;

class BaseScreen
{
    public:
        typedef BaseScreen*(*StaticConstructorPtr)(ScreensProvider *screensProvider);

        BaseScreen(ScreensProvider *screensProvider);
        static BaseScreen *staticConstructor(ScreensProvider *screensProvider);
        virtual ~BaseScreen();
        virtual BaseScreen::StaticConstructorPtr getPtrToStaticConstructor() = 0;

        virtual void load(BaseScreen::StaticConstructorPtr fromScreen) = 0;
        virtual void redraw();

        virtual BaseScreen::StaticConstructorPtr tick();

        virtual BaseScreen::StaticConstructorPtr clickUpButton();
        virtual BaseScreen::StaticConstructorPtr clickDownButton();
        virtual BaseScreen::StaticConstructorPtr clickCancelButton();
        virtual BaseScreen::StaticConstructorPtr clickOkButton();

    protected:
        ScreensProvider *_screensProvider;
        BaseScreen::StaticConstructorPtr _fromScreen;
};

#endif