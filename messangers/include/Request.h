#pragma once

#include <string>

class Request {
public:
    Request(std::string url, std::string body);

    const std::string& getUrl() const { return url; }
    const std::string& getBody() const { return body; }

private:
    std::string url;
    std::string body;
};
