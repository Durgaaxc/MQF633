#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
public:
    int year;
    int month;
    int day;

    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    Date() {}

    // Comparison operators
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    bool operator<(const Date& other) const {
        if (year < other.year) return true;
        if (year == other.year && month < other.month) return true;
        if (year == other.year && month == other.month && day < other.day) return true;
        return false;
    }

    // Subtraction operator
    double operator-(const Date& other) const {
        return (year - other.year) * 365 + (month - other.month) * 30 + (day - other.day);
    }

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.year << "-" << date.month << "-" << date.day;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Date& date) {
        char sep1, sep2;
        is >> date.year >> sep1 >> date.month >> sep2 >> date.day;
        return is;
    }
};

#endif // DATE_H
