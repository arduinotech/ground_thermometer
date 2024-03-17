#ifndef Controls_h_
#define Controls_h_

#include <Arduino.h>

class Controls
{
    public:
        Controls();
        void tick();
        bool isUpButtonPressed();
        bool isDownButtonPressed();
        bool isCancelButtonPressed();
        bool isOkButtonPressed();

    private:
        uint16_t _buttonUpLastPinValue;
        uint16_t _buttonDownLastPinValue;
        uint16_t _buttonCancelLastPinValue;
        uint16_t _buttonOkLastPinValue;

        uint32_t _lastClickUpButton;
        uint32_t _lastClickDownButton;
        uint32_t _lastClickCancelButton;
        uint32_t _lastClickOkButton;
};

#endif