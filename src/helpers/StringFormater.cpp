    #include "StringFormater.h"

String StringFormater::formatByteNum(uint8_t num)
{
    if (num < 10) {
        return String("0") + String(num);
    } else {
        return String(num);
    }
}

static String StringFormater::formatForThreeSigns(int8_t num)
{
    String value = String(num);
    if (value.length() == 0) {
        value = "   ";
    } else if (value.length() == 1) {
        value = "  " + value;
    } else if (value.length() == 2) {
        value = " " + value;
    }
    return value;
}