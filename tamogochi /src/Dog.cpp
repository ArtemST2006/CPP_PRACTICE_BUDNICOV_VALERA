#include "Dog.h"

Dog::Dog(std::string n) : Pet(n) {}

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
    mood = clamp(mood + 25);
    energy = clamp(energy - 10);
    hunger = clamp(hunger + 15);
    thirst = clamp(thirst + 15);
}

std::string Dog::getAsciiArt() const {
    MoodState state = getMoodState();
    if (state == Happy) {
        return
            "    __        \n"
            "   /  \\__     \n"
            "  ( ^.^ )_/   \n"
            "   U   U      \n";
    }
    if (state == Neutral) {
        return
            "    __        \n"
            "   /  \\__     \n"
            "  ( -.- )_/   \n"
            "   U   U      \n";
    }
    if (state == Sad) {
        return
            "    __        \n"
            "   /  \\__     \n"
            "  ( T.T )_/   \n"
            "   u   u      \n";
    }
    if (state == Sick) {
        return
            "    __        \n"
            "   /  \\__     \n"
            "  ( @.@ )_/ ~ \n"
            "   u   u      \n";
    }
    return
        "    __        \n"
        "   /  \\__     \n"
        "  ( x.x )_/   \n"
        "   _   _      \n";
}
