#include "Date.h"

double operator-(const Date& d1, const Date& d2)
{
  int yearDiff = d1.year - d2.year;
  int monthDiff = (d1.month - d2.month);
  int dayDiff = d1.day - d2.day;
  return yearDiff + monthDiff / 12.0 + dayDiff / 365.0;
}

Date DateAddDay(const Date& d1, int days)
{
  Date* newDate = new Date();
  int numOfYear = int(days/365);
  int numOfMonth = int((days - numOfYear*365)/30);
  int numofDays = days - numOfYear * 365 - numOfMonth * 30;
  newDate->day = d1.day + numofDays;
  newDate->month = d1.month + numOfMonth;
  newDate->year = d1.year + numOfYear;
  return *newDate;
}

bool operator==(const Date& d1, const Date& d2)
{
  if (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day)
    return true;
  else 
    return false;
}

bool operator<(const Date& d1, const Date& d2)
{
  if (d1-d2<0)
    return true;
  else
    return false;
}

bool operator>(const Date& d1, const Date& d2) {
  return !(d1<d2);
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
  os << d.year << " " << d.month << " " << d.day << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Date& d)
{
  is >> d.year >> d.month >> d.day;
  return is;
}
