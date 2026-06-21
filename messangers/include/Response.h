#pragma once

#include <string>

class Response {
public:
    Response(int statusCode, std::string message);

    int getStatusCode() const { return statusCode; }
    const std::string& getMessage() const { return message; }
    bool isOk() const { return statusCode == 200; }

private:
    int statusCode;
    std::string message;
};
