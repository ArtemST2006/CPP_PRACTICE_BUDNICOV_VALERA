#pragma once

#include "Service.h"

class VKClips : public Service {
public:
    VKClips(std::string accountName);
    Published publish(Content* content, Date date) override;
    std::string getName() const override;
};
