#include "Response.h"
#include <utility>

Response::Response(int sc, std::string m) : statusCode(sc), message(std::move(m)) {}
