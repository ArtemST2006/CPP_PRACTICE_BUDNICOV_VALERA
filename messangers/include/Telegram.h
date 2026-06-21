#pragma once

#include "Service.h"

class Telegram : public Service {
public:
    Telegram(std::string accountName);
    Published publish(Content* content, Date date) override;
    std::string getName() const override;
};
