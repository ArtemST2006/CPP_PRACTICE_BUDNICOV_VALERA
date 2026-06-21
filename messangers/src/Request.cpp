#include "Request.h"
#include <utility>

Request::Request(std::string u, std::string b) : url(std::move(u)), body(std::move(b)) {}
