#define NOMINMAX
#include <conio.h>
#include <Windows.h>

#include "Vector/Vector.hpp"
#include "ConsoleUtilities/ConsoleUtilities.hpp"
#include "Menu/Menu.hpp"
#include "MainMenu/MainMenu.hpp"
#include "VectorDictionary/VectorDictionary.hpp"

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_ENTER = 13;
const int KEY_ESC = 27;

int main() {
    MainMenu& mainMenu = MainMenu::GetInstance();

    for (;;) {
        Menu* currentMenu = mainMenu.GetCurrentMenu();
        if (currentMenu == nullptr) {
            break;
        }

        currentMenu->printMenu(std::cout);

        int key = _getch();
        if (key == KEY_UP) {
            currentMenu->moveIndexUp();
        }
        else if (key == KEY_DOWN) {
            currentMenu->moveIndexDown();
        }
        else if (key == KEY_ENTER) {
            currentMenu->executeActiveAction();
        }
        else if (key == KEY_ESC) {
            mainMenu.SetCurrentMenu(currentMenu->getParentMenu());
        }

        system("cls");
    }

    return 0;
}
