#include "Menu/Menu.hpp"

#include <print>
#include <ranges>
#include <iostream>

Menu::Menu(const std::string& title, std::function<void(Menu&)> action) : title(title), action(action) {
    
}

Menu& Menu::addSubmenu(Menu* menu) {
    this->submenus.push_back(menu);
    menu->parentMenu = this;

    return *this;
}

void Menu::executeAction() {
    if (action == nullptr) {
        return;
    }

    action(*this);
}

void Menu::executeActiveAction() const {
    if (submenus.empty()) {
        return;
    }

    Menu* submenu = this->submenus[this->index];
    if (submenu->action != nullptr) {
        submenu->action(*submenu);
    }
}

void Menu::printMenu(std::ostream& out) const {
    std::println(out, "{}", title);
    for (size_t i = 0; i < this->submenus.size(); ++i) {
        const Menu* menu = this->submenus[i];

        if (i == index) {
            std::print(std::cout, "> ");
        }
        else {
            std::print(std::cout, "  ");
        }

        std::println(std::cout, "{}. {}", i + 1, menu->title);
    }
}

void Menu::moveIndexDown() {
    ++this->index;
    if (this->index >= this->submenus.size()) {
        this->index = 0;
    }
}

void Menu::moveIndexUp() {
    --this->index;
    if (this->index < 0) {
        this->index = this->submenus.size() - 1;
    }
}

const Menu& Menu::getActiveSubmenu() const {
    return *this->submenus[this->index];
}

Menu& Menu::getActiveSubmenu() {
    return *this->submenus[this->index];
}

Menu* Menu::getParentMenu() const {
    return this->parentMenu;
}

const std::string& Menu::getTitle() const {
    return this->title;
}

int Menu::getIndex() const {
    return this->index;
}
