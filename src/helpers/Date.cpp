#include "Date.h"

uint8_t Date::getNumOfDaysInMonth(uint16_t year, uint8_t month)
{
	if (month == 2) {
		if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
			return 29;
        }
		return 28;
	}

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		return 31;
    }
    return 30;
}
