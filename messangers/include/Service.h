#pragma once

#include "Content.h"
#include "Published.h"
#include "Date.h"
#include <string>

class Service {
public:
    Service(std::string accountName);
    virtual ~Service() {}

    virtual Published publish(Content* content, Date date) = 0;
    virtual std::string getName() const = 0;

    const std::string& getAccount() const { return accountName; }
    void setAccount(std::string account);

protected:
    std::string accountName;
};
