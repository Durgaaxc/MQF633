#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date
{
 public:
  int year;
  int month;
  int day;
  Date(int y, int m, int d) : year(y), month(m), day(d) {};
  Date(){};
  bool isLeapYear(int year) const {
  // Standard leap year rule: divisible by 4 but not by 100 (except divisible by 400)
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
  int getDaysInMonth(int year, int month) const {
  static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 2 && isLeapYear(year)) {
    return 29;
  }
  return daysInMonth[month - 1];
}
  int adjustDay(int year, int month, int day) const {
  // Determine maximum days in the month
  int maxDays = getDaysInMonth(year, month);

  // Ensure day doesn't exceed valid range
  return std::min(day, maxDays);
}
 Date addTimeStep(const std::string& timestep) const {
        // Create a copy to avoid modifying original object
        Date newDate = *this;

        int numUnits;
        char unit = timestep.back();

        // Extract number and unit (M or Y)
        try {
            numUnits = std::stoi(timestep.substr(0, timestep.size() - 1));
            if (numUnits < 0) {
                throw std::invalid_argument("Invalid timestep: negative value");
            }
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid timestep format: " + std::string(e.what()));
        }

        if (unit == 'M') {
            newDate.month += numUnits;
        } else if (unit == 'Y') {
            newDate.year += numUnits;
        } else {
            throw std::invalid_argument("Invalid timestep unit: " + unit);
        }

        // Adjust for year rollovers and day validity
        while (newDate.month > 12) {
            newDate.month -= 12;
            newDate.year++;
        }
        while (newDate.month < 1) {
            newDate.month += 12;
            newDate.year--;
        }
        newDate.day = adjustDay(newDate.year, newDate.month, newDate.day);

        return newDate;
    }
};


double operator-(const Date& d1, const Date& d2);
std::ostream& operator<<(std::ostream& os, const Date& date);
std::istream& operator>>(std::istream& is, Date& date);

#endif
