#include "Rtc.h"

Rtc *Rtc::_instance = NULL;

Rtc *Rtc::getInstance()
{
    if (NULL == _instance) {
        _instance = new Rtc();
    }
    return _instance;
}

MicroDS3231 *Rtc::getRtc()
{
    return _rtc;
}

Rtc::Rtc()
{
    _rtc = new MicroDS3231();
}
