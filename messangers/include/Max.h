#pragma once

#include "Service.h"

class Max : public Service {
public:
    Max(std::string accountName);
    Published publish(Content* content, Date date) override;
    std::string getName() const override;
};
