#include "Cat.h"

Cat::Cat(std::string n) : Pet(n) {}

std::string Cat::voice() const {
    return "Мяу!";
}

std::string Cat::species() const {
    return "кот";
}

std::string Cat::specialActionName() const {
    return "Помурлыкать";
}

void Cat::specialAction() {
    mood = clamp(mood + 30);
    energy = clamp(energy - 5);
}

std::string Cat::getAsciiArt() const {
    MoodState state = getMoodState();
    if (state == Happy) {
        return
            "   /\\_/\\   \n"
            "  ( ^.^ )  \n"
            "   > ^ <   \n";
    }
    if (state == Neutral) {
        return
            "   /\\_/\\   \n"
            "  ( -.- )  \n"
            "   > o <   \n";
    }
    if (state == Sad) {
        return
            "   /\\_/\\   \n"
            "  ( T.T )  \n"
            "   > _ <   \n";
    }
    if (state == Sick) {
        return
            "   /\\_/\\   \n"
            "  ( @.@ )~ \n"
            "   > ~ <   \n";
    }
    return
        "   /\\_/\\   \n"
        "  ( x.x )  \n"
        "   > - <   \n";
}
