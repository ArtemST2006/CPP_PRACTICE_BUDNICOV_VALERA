#include "Pet.h"

Pet::Pet(std::string n) {
    name = n;
    hp = 100;
    hunger = 30;
    thirst = 30;
    mood = 70;
    energy = 80;
    age = 0;
}

int Pet::clamp(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

void Pet::feed() {
    hunger = clamp(hunger - 30);
    thirst = clamp(thirst + 5);
}

void Pet::drink() {
    thirst = clamp(thirst - 30);
}

void Pet::play() {
    mood = clamp(mood + 20);
    energy = clamp(energy - 15);
    hunger = clamp(hunger + 10);
    thirst = clamp(thirst + 10);
}

void Pet::sleep() {
    energy = clamp(energy + 40);
    hunger = clamp(hunger + 10);
    thirst = clamp(thirst + 5);
}

void Pet::tick() {
    age = age + 1;
    hunger = clamp(hunger + 3);
    thirst = clamp(thirst + 4);
    mood = clamp(mood - 2);
    energy = clamp(energy - 2);

    int damage = 0;
    if (hunger >= 90) damage += 2;
    if (thirst >= 90) damage += 3;
    if (mood <= 10) damage += 1;
    if (energy <= 5) damage += 1;
    hp = clamp(hp - damage);
}

bool Pet::isAlive() const {
    return hp > 0;
}

MoodState Pet::getMoodState() const {
    if (hp <= 0) return Dead;
    if (hp <= 30) return Sick;
    int avg = (mood + (100 - hunger) + (100 - thirst)) / 3;
    if (avg >= 65) return Happy;
    if (avg >= 35) return Neutral;
    return Sad;
}
