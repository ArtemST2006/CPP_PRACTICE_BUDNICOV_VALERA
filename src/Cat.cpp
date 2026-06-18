#include "Cat.h"

Cat::Cat(const std::string& name) : Pet(name) {}

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
    mood_ = clamp(mood_ + 30);
    energy_ = clamp(energy_ - 5);
}

std::string Cat::getAsciiArt() const {
    switch (getMoodState()) {
        case MoodState::Happy:
            return
                "   /\\_/\\   \n"
                "  ( ^.^ )  \n"
                "   > ^ <   \n";
        case MoodState::Neutral:
            return
                "   /\\_/\\   \n"
                "  ( -.- )  \n"
                "   > o <   \n";
        case MoodState::Sad:
            return
                "   /\\_/\\   \n"
                "  ( T.T )  \n"
                "   > _ <   \n";
        case MoodState::Sick:
            return
                "   /\\_/\\   \n"
                "  ( @.@ )~ \n"
                "   > ~ <   \n";
        case MoodState::Dead:
        default:
            return
                "   /\\_/\\   \n"
                "  ( x.x )  \n"
                "   > - <   \n";
    }
}
