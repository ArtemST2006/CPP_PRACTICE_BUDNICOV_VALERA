#include "Date.h"
#include <stdexcept>
#include <iomanip>

Date::Date() : day(1), month(1), year(2025), hour(0), minute(0) {}

Date::Date(int d, int m, int y, int h, int mi) : day(d), month(m), year(y), hour(h), minute(mi) {
    if (d < 1 || d > 31) throw std::invalid_argument("День должен быть в диапазоне 1..31");
    if (m < 1 || m > 12) throw std::invalid_argument("Месяц должен быть в диапазоне 1..12");
    if (y < 1970 || y > 9999) throw std::invalid_argument("Год должен быть в диапазоне 1970..9999");
    if (h < 0 || h > 23) throw std::invalid_argument("Час должен быть в диапазоне 0..23");
    if (mi < 0 || mi > 59) throw std::invalid_argument("Минута должна быть в диапазоне 0..59");
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << std::setfill('0') << std::setw(2) << d.day << "."
       << std::setw(2) << d.month << "."
       << std::setw(4) << d.year << " "
       << std::setw(2) << d.hour << ":"
       << std::setw(2) << d.minute
       << std::setfill(' ');
    return os;
}
