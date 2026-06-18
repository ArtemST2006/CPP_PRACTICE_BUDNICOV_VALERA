#pragma once

#include <string>

enum class MoodState {
    Happy,
    Neutral,
    Sad,
    Sick,
    Dead
};

class Pet {
public:
    Pet(const std::string& name);
    virtual ~Pet() = default;

    void feed();
    void drink();
    void play();
    void sleep();
    void tick();

    bool isAlive() const;
    MoodState getMoodState() const;

    const std::string& getName() const { return name_; }
    int getHp() const { return hp_; }
    int getHunger() const { return hunger_; }
    int getThirst() const { return thirst_; }
    int getMood() const { return mood_; }
    int getEnergy() const { return energy_; }
    int getAge() const { return age_; }

    virtual std::string voice() const = 0;
    virtual std::string species() const = 0;
    virtual std::string specialActionName() const = 0;
    virtual void specialAction() = 0;
    virtual std::string getAsciiArt() const = 0;

protected:
    static int clamp(int v, int lo = 0, int hi = 100);

    std::string name_;
    int hp_ = 100;
    int hunger_ = 30;
    int thirst_ = 30;
    int mood_ = 70;
    int energy_ = 80;
    int age_ = 0;
};
