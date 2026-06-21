#pragma once

#include "Pet.h"

class Dog : public Pet {
public:
    Dog(std::string n);

    std::string voice() const override;
    std::string species() const override;
    std::string specialActionName() const override;
    void specialAction() override;
    std::string getAsciiArt() const override;
};
