#include "Date.h"

double operator-(const Date& d1, const Date& d2) {
    int yearDiff = d1.year - d2.year;
    int monthDiff = (d1.month - d2.month);
    int dayDiff = d1.day - d2.day;
    return yearDiff + monthDiff / 12.0 + dayDiff / 365.0;
}
