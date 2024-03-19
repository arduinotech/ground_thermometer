#ifndef Rtc_h_
#define Rtc_h_

#include <microDS3231.h>

class Rtc
{
    public:
        static Rtc *getInstance();
        MicroDS3231 *getRtc();

    protected:
        Rtc();

    private:
        static Rtc *_instance;
        MicroDS3231 *_rtc;
};

#endif