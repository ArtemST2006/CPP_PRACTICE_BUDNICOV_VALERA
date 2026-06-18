#pragma once

#include <string>
#include "Pet.h"

namespace ui {

void init();
void shutdown();

int showWelcome();
std::string askName();

void renderGame(const Pet& pet);
int askMenuChoice(const Pet& pet);

void showMessage(const std::string& msg);
void showDeathScreen(const Pet& pet);

enum class ActionAnim {
    Feed,
    Drink,
    Play,
    Sleep,
    Special,
};

void animateAction(const Pet& pet, ActionAnim kind);

}
