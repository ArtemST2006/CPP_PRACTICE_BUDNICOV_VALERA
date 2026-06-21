#include "Published.h"
#include <utility>

Published::Published(Content* c, std::string svc, std::string account, Date d)
    : content(c), serviceName(std::move(svc)), accountName(std::move(account)), date(d) {}

std::ostream& operator<<(std::ostream& os, const Published& p) {
    os << "[" << p.date << "] " << p.serviceName << " (@" << p.accountName << ") -> ";
    if (p.content != nullptr) {
        os << p.content->getSummary();
    } else {
        os << "(пустой контент)";
    }
    return os;
}
