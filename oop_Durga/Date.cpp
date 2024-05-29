#include "Date.h"

// Comparison operators
bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator<=(const Date& other) const {
    return *this < other || *this == other;
}

bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator>(const Date& other) const {
    return !(*this <= other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

// Operator to compute the difference between two dates
double operator-(const Date& d1, const Date& d2) {
    int yearDiff = d1.year - d2.year;
    int monthDiff = d1.month - d2.month;
    int dayDiff = d1.day - d2.day;
    return yearDiff + monthDiff / 12.0 + dayDiff / 365.0;
}

// Output operator
std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << d.year << " " << d.month << " " << d.day;
    return os;
}

// Input operator
std::istream& operator>>(std::istream& is, Date& d) {
    is >> d.year >> d.month >> d.day;
    return is;
}
