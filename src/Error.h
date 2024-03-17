#ifndef Error_h_
#define Error_h_

#include <Arduino.h>

class Error
{
    public:
        static void throwError(String message);
};

#endif