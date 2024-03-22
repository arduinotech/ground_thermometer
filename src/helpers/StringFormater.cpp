#include "StringFormater.h"

String StringFormater::formatByteNum(uint8_t num)
{
    if (num < 10) {
        return String("0") + String(num);
    } else {
        return String(num);
    }
}
