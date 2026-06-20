#pragma once

#include <string>

enum MoodState {
    Happy,
    Neutral,
    Sad,
    Sick,
    Dead
};

class Pet {
public:
    Pet(std::string n);
    virtual ~Pet() {}

    void feed();
    void drink();
    void play();
    void sleep();
    void tick();

    bool isAlive() const;
    MoodState getMoodState() const;

    std::string getName() const { return name; }
    int getHp() const { return hp; }
    int getHunger() const { return hunger; }
    int getThirst() const { return thirst; }
    int getMood() const { return mood; }
    int getEnergy() const { return energy; }
    int getAge() const { return age; }

    virtual std::string voice() const = 0;
    virtual std::string species() const = 0;
    virtual std::string specialActionName() const = 0;
    virtual void specialAction() = 0;
    virtual std::string getAsciiArt() const = 0;

protected:
    static int clamp(int v, int lo = 0, int hi = 100);

    std::string name;
    int hp;
    int hunger;
    int thirst;
    int mood;
    int energy;
    int age;
};
