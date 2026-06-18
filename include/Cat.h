#pragma once

#include "Pet.h"

class Cat : public Pet {
public:
    Cat(const std::string& name);

    std::string voice() const override;
    std::string species() const override;
    std::string specialActionName() const override;
    void specialAction() override;
    std::string getAsciiArt() const override;
};
