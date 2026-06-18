#include <memory>
#include <stdexcept>

#include "Cat.h"
#include "Dog.h"
#include "Pet.h"
#include "Ui.h"

void renderPet(Pet* pet) {
    ui::renderGame(*pet);
}

std::unique_ptr<Pet> choosePet() {
    int choice = ui::showWelcome();
    std::string name = ui::askName();
    if (choice == 1) {
        return std::make_unique<Cat>(name);
    }
    return std::make_unique<Dog>(name);
}

void handleAction(Pet* pet, int choice) {
    switch (choice) {
        case 1:
            pet->feed();
            ui::animateAction(*pet, ui::ActionAnim::Feed);
            ui::showMessage("Питомец поел.");
            break;
        case 2:
            pet->drink();
            ui::animateAction(*pet, ui::ActionAnim::Drink);
            ui::showMessage("Питомец попил.");
            break;
        case 3:
            pet->play();
            ui::animateAction(*pet, ui::ActionAnim::Play);
            ui::showMessage("Поиграли вместе!");
            break;
        case 4:
            pet->sleep();
            ui::animateAction(*pet, ui::ActionAnim::Sleep);
            ui::showMessage("Питомец поспал.");
            break;
        case 5:
            pet->specialAction();
            ui::animateAction(*pet, ui::ActionAnim::Special);
            ui::showMessage(pet->specialActionName() + " — выполнено!");
            break;
        default:
            break;
    }
}

int main() {
    ui::init();
    try {
        auto pet = choosePet();

        while (pet->isAlive()) {
            renderPet(pet.get());
            int choice = ui::askMenuChoice(*pet);
            if (choice == 6) break;
            if (choice >= 1 && choice <= 5) {
                handleAction(pet.get(), choice);
            }
            pet->tick();
        }

        if (!pet->isAlive()) {
            ui::showDeathScreen(*pet);
        }
    } catch (...) {
        ui::shutdown();
        throw;
    }
    ui::shutdown();
    return 0;
}
