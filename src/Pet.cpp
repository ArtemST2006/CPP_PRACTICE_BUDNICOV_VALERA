#include "Pet.h"

Pet::Pet(const std::string& name) : name_(name) {}

int Pet::clamp(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

void Pet::feed() {
    hunger_ = clamp(hunger_ - 30);
    thirst_ = clamp(thirst_ + 5);
}

void Pet::drink() {
    thirst_ = clamp(thirst_ - 30);
}

void Pet::play() {
    mood_ = clamp(mood_ + 20);
    energy_ = clamp(energy_ - 15);
    hunger_ = clamp(hunger_ + 10);
    thirst_ = clamp(thirst_ + 10);
}

void Pet::sleep() {
    energy_ = clamp(energy_ + 40);
    hunger_ = clamp(hunger_ + 10);
    thirst_ = clamp(thirst_ + 5);
}

void Pet::tick() {
    ++age_;
    hunger_ = clamp(hunger_ + 3);
    thirst_ = clamp(thirst_ + 4);
    mood_ = clamp(mood_ - 2);
    energy_ = clamp(energy_ - 2);

    int damage = 0;
    if (hunger_ >= 90) damage += 2;
    if (thirst_ >= 90) damage += 3;
    if (mood_ <= 10) damage += 1;
    if (energy_ <= 5) damage += 1;
    hp_ = clamp(hp_ - damage);
}

bool Pet::isAlive() const {
    return hp_ > 0;
}

MoodState Pet::getMoodState() const {
    if (hp_ <= 0) return MoodState::Dead;
    if (hp_ <= 30) return MoodState::Sick;
    int avg = (mood_ + (100 - hunger_) + (100 - thirst_)) / 3;
    if (avg >= 65) return MoodState::Happy;
    if (avg >= 35) return MoodState::Neutral;
    return MoodState::Sad;
}
