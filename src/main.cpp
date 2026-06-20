#include "Cat.h"
#include "Dog.h"
#include "Pet.h"
#include "Ui.h"

void renderPet(Pet* pet) {
    renderGame(*pet);
}

Pet* choosePet() {
    int choice = showWelcome();
    std::string name = askName();
    if (choice == 1) {
        return new Cat(name);
    }
    return new Dog(name);
}

void handleAction(Pet* pet, int choice) {
    if (choice == 1) {
        pet->feed();
        animateAction(*pet, AnimFeed);
        showMessage("Питомец поел.");
    } else if (choice == 2) {
        pet->drink();
        animateAction(*pet, AnimDrink);
        showMessage("Питомец попил.");
    } else if (choice == 3) {
        pet->play();
        animateAction(*pet, AnimPlay);
        showMessage("Поиграли вместе!");
    } else if (choice == 4) {
        pet->sleep();
        animateAction(*pet, AnimSleep);
        showMessage("Питомец поспал.");
    } else if (choice == 5) {
        pet->specialAction();
        animateAction(*pet, AnimSpecial);
        showMessage(pet->specialActionName() + " — выполнено!");
    }
}

int main() {
    uiInit();

    Pet* pet = choosePet();

    while (pet->isAlive()) {
        renderPet(pet);
        int choice = askMenuChoice(*pet);
        if (choice == 6) break;
        if (choice >= 1 && choice <= 5) {
            handleAction(pet, choice);
        }
        pet->tick();
    }

    if (!pet->isAlive()) {
        showDeathScreen(*pet);
    }

    delete pet;
    uiShutdown();
    return 0;
}
