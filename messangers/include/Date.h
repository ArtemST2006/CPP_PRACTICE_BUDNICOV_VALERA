#pragma once

#include <ostream>

class Date {
public:
    Date();
    Date(int day, int month, int year, int hour, int minute);

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }

    friend std::ostream& operator<<(std::ostream& os, const Date& d);

private:
    int day;
    int month;
    int year;
    int hour;
    int minute;
};
