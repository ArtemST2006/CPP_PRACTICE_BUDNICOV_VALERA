#include "Service.h"
#include <utility>

Service::Service(std::string a) : accountName(std::move(a)) {}

void Service::setAccount(std::string a) {
    accountName = std::move(a);
}
