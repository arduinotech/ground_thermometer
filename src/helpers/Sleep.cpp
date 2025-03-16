#include "Sleep.h"

Sleep *Sleep::_instance = nullptr;

Sleep *Sleep::getInstance()
{
    if (nullptr == _instance) {
        _instance = new Sleep();
    }
    return _instance;
}

void Sleep::setWakeUpByInterrupt(bool value)
{
    _wakeUpByInterrupt = value;
}

Sleep::Sleep()
{

}
