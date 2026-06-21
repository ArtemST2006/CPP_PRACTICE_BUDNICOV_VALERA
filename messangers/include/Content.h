#pragma once

#include <string>

class Content {
public:
    virtual ~Content();
    virtual std::string getType() const = 0;
    virtual std::string getSummary() const = 0;
};
