#include "Dog.h"

Dog::Dog(const std::string& name) : Pet(name) {}

std::string Dog::voice() const {
    return "Гав!";
}

std::string Dog::species() const {
    return "собака";
}

std::string Dog::specialActionName() const {
    return "Погулять";
}

void Dog::specialAction() {
    mood_ = clamp(mood_ + 25);
    energy_ = clamp(energy_ - 10);
    hunger_ = clamp(hunger_ + 15);
    thirst_ = clamp(thirst_ + 15);
}

std::string Dog::getAsciiArt() const {
    switch (getMoodState()) {
        case MoodState::Happy:
            return
                "    __        \n"
                "   /  \\__     \n"
                "  ( ^.^ )_/   \n"
                "   U   U      \n";
        case MoodState::Neutral:
            return
                "    __        \n"
                "   /  \\__     \n"
                "  ( -.- )_/   \n"
                "   U   U      \n";
        case MoodState::Sad:
            return
                "    __        \n"
                "   /  \\__     \n"
                "  ( T.T )_/   \n"
                "   u   u      \n";
        case MoodState::Sick:
            return
                "    __        \n"
                "   /  \\__     \n"
                "  ( @.@ )_/ ~ \n"
                "   u   u      \n";
        case MoodState::Dead:
        default:
            return
                "    __        \n"
                "   /  \\__     \n"
                "  ( x.x )_/   \n"
                "   _   _      \n";
    }
}
