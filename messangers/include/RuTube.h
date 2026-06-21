#pragma once

#include "Service.h"

class RuTube : public Service {
public:
    RuTube(std::string accountName);
    Published publish(Content* content, Date date) override;
    std::string getName() const override;
};
