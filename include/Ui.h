#pragma once

#include <string>
#include "Pet.h"

enum ActionAnim {
    AnimFeed,
    AnimDrink,
    AnimPlay,
    AnimSleep,
    AnimSpecial
};

void uiInit();
void uiShutdown();

int showWelcome();
std::string askName();

void renderGame(const Pet& pet);
int askMenuChoice(const Pet& pet);

void showMessage(const std::string& msg);
void animateAction(const Pet& pet, ActionAnim kind);
void showDeathScreen(const Pet& pet);
