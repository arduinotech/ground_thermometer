#include "Controls.h"
#include "hardware/Config.h"

Controls::Controls()
{
    pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
    pinMode(PIN_BUTTON_DOWN, INPUT_PULLUP);
    pinMode(PIN_BUTTON_CANCEL, INPUT_PULLUP);
    pinMode(PIN_BUTTON_OK, INPUT_PULLUP);

    digitalWrite(PIN_BUTTON_UP, HIGH);
    digitalWrite(PIN_BUTTON_DOWN, HIGH);
    digitalWrite(PIN_BUTTON_CANCEL, HIGH);
    digitalWrite(PIN_BUTTON_OK, HIGH);

    _lastClickUpButton = millis();
    _lastClickDownButton = millis();
    _lastClickCancelButton = millis();
    _lastClickOkButton = millis();
}

void Controls::tick()
{
    _buttonUpLastPinValue = digitalRead(PIN_BUTTON_UP);
    _buttonDownLastPinValue = digitalRead(PIN_BUTTON_DOWN);
    _buttonCancelLastPinValue = digitalRead(PIN_BUTTON_CANCEL);
    _buttonOkLastPinValue = digitalRead(PIN_BUTTON_OK);
}

bool Controls::isUpButtonPressed()
{
    uint32_t now = millis();

    if (now < _lastClickUpButton) {
        _lastClickUpButton = 0;
        return false;
    }

    if ((now - _lastClickUpButton) < BUTTON_PRESS_DELAY_MILLIS) {
        return false;
    }

    if (LOW == _buttonUpLastPinValue) {
        _lastClickUpButton = now;
        return true;
    }
    return false;
}

bool Controls::isDownButtonPressed()
{
    uint32_t now = millis();

    if (now < _lastClickDownButton) {
        _lastClickDownButton = 0;
        return false;
    }

    if ((now - _lastClickDownButton) < BUTTON_PRESS_DELAY_MILLIS) {
        return false;
    }

    if (LOW == _buttonDownLastPinValue) {
        _lastClickDownButton = now;
        return true;
    }
    return false;
}

bool Controls::isCancelButtonPressed()
{
    uint32_t now = millis();

    if (now < _lastClickCancelButton) {
        _lastClickCancelButton = 0;
        return false;
    }

    if ((now - _lastClickCancelButton) < BUTTON_PRESS_DELAY_MILLIS) {
        return false;
    }

    if (LOW == _buttonCancelLastPinValue) {
        _lastClickCancelButton = now;
        return true;
    }
    return false;
}

bool Controls::isOkButtonPressed()
{
    uint32_t now = millis();

    if (now < _lastClickOkButton) {
        _lastClickOkButton = 0;
        return false;
    }

    if ((now - _lastClickOkButton) < BUTTON_PRESS_DELAY_MILLIS) {
        return false;
    }

    if (LOW == _buttonOkLastPinValue) {
        _lastClickOkButton = now;
        return true;
    }
    return false;
}
