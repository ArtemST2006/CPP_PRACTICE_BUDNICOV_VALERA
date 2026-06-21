#pragma once

#include "Content.h"
#include "Date.h"
#include <string>
#include <ostream>

class Published {
public:
    Published(Content* content, std::string serviceName, std::string accountName, Date date);

    const Content* getContent() const { return content; }
    const std::string& getServiceName() const { return serviceName; }
    const std::string& getAccountName() const { return accountName; }
    const Date& getDate() const { return date; }

    friend std::ostream& operator<<(std::ostream& os, const Published& p);

private:
    Content*    content;
    std::string serviceName;
    std::string accountName;
    Date        date;
};
