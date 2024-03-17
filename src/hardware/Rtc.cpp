#include "Rtc.h"

Rtc *Rtc::_instance = NULL;

Rtc *Rtc::getInstance()
{
    if (NULL == _instance) {
        _instance = new Rtc();
    }
    return _instance;
}

String Rtc::getDateString()
{
    return _rtc->getDateString();
}

String Rtc::getTimeString()
{
    return _rtc->getTimeString();
}

Rtc::Rtc()
{
    _rtc = new MicroDS3231();
}
