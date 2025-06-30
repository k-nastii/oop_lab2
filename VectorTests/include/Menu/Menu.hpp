#pragma once
#include <string>
#include <functional>
#include <vector>
#include <ostream>

class Menu {
public:
    Menu(const std::string& title, std::function<void(Menu&)> action);

    Menu& addSubmenu(Menu* menu);

    void executeAction();
    void executeActiveAction() const;

    void printMenu(std::ostream& out) const;

    void moveIndexDown();
    void moveIndexUp();

    const Menu& getActiveSubmenu() const;
    Menu& getActiveSubmenu();
    Menu* getParentMenu() const;
    const std::string& getTitle() const;
    int getIndex() const;

private:
    std::vector<Menu*> submenus{};
    Menu* parentMenu{};
    std::string title{};
    std::function<void(Menu&)> action{};
    int index{};
};
