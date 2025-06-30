#include "MainMenu/MainMenu.hpp"
#include "VectorDictionary/VectorDictionary.hpp"
#include "ConsoleUtilities/ConsoleUtilities.hpp"

#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <filesystem>
#include <functional>
#include <algorithm>
#include <ranges>
#include <print>

MainMenu& MainMenu::GetInstance() {
    static MainMenu instance{};
    return instance;
}

MainMenu::MainMenu() {
    this->CreateMenus();
}

MainMenu::~MainMenu() {
    for (auto& [_, value] : this->menus) {
        delete value;
    }
}

Menu* MainMenu::GetCurrentMenu() {
    return this->currentMenu;
}

void MainMenu::SetCurrentMenu(Menu* menu) {
    this->currentMenu = menu;
}

void MainMenu::CreateMenus() {
    this->CreateBackMenu();
    this->CreateFromCLIMenu();
    this->CreateFromFileMenu();
    this->CreateFromExistingMenu();
    this->CreateSumMenu();
    this->CreateDiffMenu();
    this->CreateMultMenu();
    this->CreateNormalizeMenu();
    this->CreateScalarMenu();
    this->CreateVectorMenu();
    this->CreateAddMenu();
    this->CreateOperationsMenu();
    this->CreateSaveMenu();
    this->CreatePrintMenu();
    this->CreateQuitMenu();
    this->CreateMainMenu();
    this->SetCurrentMenu(this->menus.at("Main"));
}

void MainMenu::CreateBackMenu() {
    Menu* backMenu = new Menu("Back", [this](Menu&) {
        this->SetCurrentMenu(this->menus.at("Main"));
    });
    this->menus.emplace(this->BackKey, backMenu);
}

void MainMenu::CreateFromCLIMenu() {
    Menu* addVectorFromCLIMenu = new Menu("From CLI", [](Menu&) { 
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string name = ConsoleUtilities::GetString(std::cin, "Print name");
        const lab::Vector vector = ConsoleUtilities::GetVector(std::cin, "Fill vector");

        vectorDictionary.Add(name, vector);
        std::cout << "Vector \"" << name << "\" with value " << vector << " was created!" << std::endl;

        system("pause");
    });
    this->menus.emplace(this->FromCLIKey, addVectorFromCLIMenu);
}

void MainMenu::CreateFromFileMenu() {
    Menu* addVectorFromFileMenu = new Menu("From file", [](Menu&) {
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string filepath = ConsoleUtilities::GetString(std::cin, "Print filepath");
        if (!std::filesystem::exists(filepath)) {
            std::println(std::cout, "This filepath doesn't exist {}!", filepath);
            system("pause");
            return;
        }

        const std::string name = ConsoleUtilities::GetString(std::cin, "Print name");
        std::fstream in(filepath, std::fstream::in);
        const lab::Vector vector = ConsoleUtilities::GetVector(in, "Fill vector");
        vectorDictionary.Add(name, vector);

        std::cout << "Vector \"" << name << "\" with value " << vector << " was created!" << std::endl;

        system("pause");
    });
    this->menus.emplace(this->FromFileKey, addVectorFromFileMenu);
}

void MainMenu::CreateFromExistingMenu() {
    Menu* addVectorFromExistingMenu = new Menu("From existing", [](Menu&) {
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string newName = ConsoleUtilities::GetString(std::cin, "Print new name");
        const std::string existingName = ConsoleUtilities::GetString(std::cin, "Print existing name");

        if (newName == existingName) {
            std::println(std::cout, "You entered same names!");
            system("pause");
            return;
        }

        if (!vectorDictionary.Contains(existingName, std::format("Vector with \"{}\" name doesn't exist!", existingName))){
            system("pause");
            return;
        }

        vectorDictionary.Add(newName, vectorDictionary[existingName]);
        std::cout << "Vector \"" << newName << "\" with value " << vectorDictionary[newName] << " was created!" << std::endl;

        system("pause");
    });
    this->menus.emplace(this->FromExistKey, addVectorFromExistingMenu);
}

void MainMenu::CreateSumMenu() {
    Menu* sumOperationMenu = new Menu("Sum", [](Menu&) {
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string firstName = ConsoleUtilities::GetString(std::cin, "Print first name of the vector");
        if (!vectorDictionary.Contains(firstName, std::format("Vector with \"{}\" name doesn't exist!", firstName))) {
            system("pause");
            return;
        }
        
        const std::string secondName = ConsoleUtilities::GetString(std::cin, "Print second name of the vector");
        if (!vectorDictionary.Contains(secondName, std::format("Vector with \"{}\" name doesn't exist!", firstName))) {
            system("pause");
            return;
        }

        const std::string resultName = ConsoleUtilities::GetString(std::cin, "Print a name of the new vector");
        const lab::Vector firstVector = vectorDictionary[firstName];
        const lab::Vector secondVector = vectorDictionary[secondName];

        const lab::Vector resultVector = firstVector + secondVector;
        vectorDictionary.Add(resultName, resultVector);

        std::cout << firstVector << " + " << secondVector << " = " << resultVector << std::endl;
        system("pause");
    });
    this->menus.emplace(this->SumKey, sumOperationMenu);
}

void MainMenu::CreateDiffMenu() {
    Menu* diffOperationMenu = new Menu("Diff", [](Menu&) { 
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string firstName = ConsoleUtilities::GetString(std::cin, "Print first name of the vector");
        if (!vectorDictionary.Contains(firstName, std::format("Vector with \"{}\" name doesn't exist!", firstName))) {
            system("pause");
            return;
        }
        
        const std::string secondName = ConsoleUtilities::GetString(std::cin, "Print second name of the vector");
        if (!vectorDictionary.Contains(secondName, std::format("Vector with \"{}\" name doesn't exist!", firstName))) {
            system("pause");
            return;
        }

        const std::string resultName = ConsoleUtilities::GetString(std::cin, "Print a name of the new vector");
        const lab::Vector firstVector = vectorDictionary[firstName];
        const lab::Vector secondVector = vectorDictionary[secondName];

        const lab::Vector resultVector = firstVector - secondVector;
        vectorDictionary.Add(resultName, resultVector);

        std::cout << firstVector << " - " << secondVector << " = " << resultVector << std::endl;
        system("pause");
    });
    this->menus.emplace(this->DiffKey, diffOperationMenu);
}

void MainMenu::CreateMultMenu() {
    Menu* multOperationMenu = new Menu("Mult", [](Menu& menu) { 
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string name = ConsoleUtilities::GetString(std::cin, "Print a name of the vector");
        if (!vectorDictionary.Contains(name, std::format("Vector with \"{}\" name doesn't exist!", name))) {
            system("pause");
            return;
        }

        const double scalar = ConsoleUtilities::GetDouble(std::cin, "Print any number");
        const std::string resultName = ConsoleUtilities::GetString(std::cin, "Print a name of the new vector");
        const lab::Vector vector = vectorDictionary[name];
        const lab::Vector resultVector = vector * scalar;

        vectorDictionary.Add(resultName, resultVector);

        std::cout << vector << " * " << scalar << " = " << resultVector << std::endl;
        system("pause");
    });
    this->menus.emplace(this->MultKey, multOperationMenu);
}

void MainMenu::CreateNormalizeMenu() {
    Menu* normalizeOperationMenu = new Menu("Normalize", [](Menu& menu) {
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string name = ConsoleUtilities::GetString(std::cin, "Print a name of the vector");
        if (!vectorDictionary.Contains(name, std::format("Vector with \"{}\" name doesn't exist!", name))) {
            system("pause");
            return;
        }

        const std::string resultName = ConsoleUtilities::GetString(std::cin, "Print a name of the new vector");
        const lab::Vector vector = vectorDictionary[name];
        const lab::Vector resultVector = vector.Normalize();

        vectorDictionary.Add(resultName, resultVector);

        std::cout << vector << " normal is " << resultVector << std::endl;
        system("pause");
    });
    this->menus.emplace(this->NormalizeKey, normalizeOperationMenu);
}

void MainMenu::CreateScalarMenu() {
    Menu* scalarProductOperationMenu = new Menu("Scalar product", [](Menu& menu) {
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string firstName = ConsoleUtilities::GetString(std::cin, "Print first name of the vector");
        if (!vectorDictionary.Contains(firstName, std::format("Vector with \"{}\" name doesn't exist!", firstName))) {
            system("pause");
            return;
        }
        
        const std::string secondName = ConsoleUtilities::GetString(std::cin, "Print second name of the vector");
        if (!vectorDictionary.Contains(secondName, std::format("Vector with \"{}\" name doesn't exist!", secondName))) {
            system("pause");
            return;
        }

        const lab::Vector firstVector = vectorDictionary[firstName];
        const lab::Vector secondVector = vectorDictionary[secondName];
        const double result = firstVector.Dot(secondVector);

        std::cout << firstVector << " * " << secondVector << " = " << result << std::endl;
        system("pause");
    });
    this->menus.emplace(this->ScalarKey, scalarProductOperationMenu);
}

void MainMenu::CreateVectorMenu() {
   Menu* vectorProductOperationMenu = new Menu("Vector product", [](Menu& menu) { 
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string firstName = ConsoleUtilities::GetString(std::cin, "Print first name of the vector");
        if (!vectorDictionary.Contains(firstName, std::format("Vector with \"{}\" name doesn't exist!", firstName))) {
            system("pause");
            return;
        }
        
        const std::string secondName = ConsoleUtilities::GetString(std::cin, "Print second name of the vector");
        if (!vectorDictionary.Contains(secondName, std::format("Vector with \"{}\" name doesn't exist!", secondName))) {
            system("pause");
            return;
        }

        const lab::Vector firstVector = vectorDictionary[firstName];
        const lab::Vector secondVector = vectorDictionary[secondName];
        if (firstVector.GetDimentionsCount() != secondVector.GetDimentionsCount() || firstVector.GetDimentionsCount() != 3) {
            std::println(std::cout, "Impossible to do this operation with these vectors!");
            system("pause");
            return;
        }

        const std::string resultName = ConsoleUtilities::GetString(std::cin, "Print a name of the new vector");
        const lab::Vector resultVector = firstVector.Cross(secondVector);

        vectorDictionary.Add(resultName, resultVector);

        std::cout << firstVector << " x " << secondVector << " = " << resultVector << std::endl;
        system("pause");
    });
    this->menus.emplace(this->VectorKey, vectorProductOperationMenu);
}

void MainMenu::CreateAddMenu() {
    Menu* addVectorMenu = new Menu("Add vector", [this](Menu& menu) {
        this->SetCurrentMenu(&menu);
    });

    (*addVectorMenu)
        .addSubmenu(this->menus.at(this->FromCLIKey))
        .addSubmenu(this->menus.at(this->FromFileKey))
        .addSubmenu(this->menus.at(this->FromExistKey))
        .addSubmenu(this->menus.at(this->BackKey));

    this->menus.emplace(this->AddKey, addVectorMenu);
}

void MainMenu::CreateOperationsMenu() {
    Menu* operationsMenu = new Menu("Operations with vector", [this](Menu& menu) {
        this->SetCurrentMenu(&menu);
    });

    operationsMenu
        ->addSubmenu(this->menus.at(this->SumKey))
        .addSubmenu(this->menus.at(this->DiffKey))
        .addSubmenu(this->menus.at(this->MultKey))
        .addSubmenu(this->menus.at(this->NormalizeKey))
        .addSubmenu(this->menus.at(this->ScalarKey))
        .addSubmenu(this->menus.at(this->VectorKey))
        .addSubmenu(this->menus.at(this->BackKey));

    this->menus.emplace(this->OperationsKey, operationsMenu);
}

void MainMenu::CreateSaveMenu() {
    Menu* saveVectorMenu = new Menu("Save vector", [](Menu&) {
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        const std::string filepath = ConsoleUtilities::GetString(std::cin, "Print filepath");
        const std::string name = ConsoleUtilities::GetString(std::cin, "Print a name of the vector");
        if (!vectorDictionary.Contains(name, std::format("Vector with \"{}\" name doesn't exist!", name))) {
            system("pause");
            return;
        }

        std::fstream out(filepath, std::fstream::out);
        const lab::Vector& vector = vectorDictionary[name];
        out << vector << std::endl;

        std::cout << "Vector \"" << name << "\" with value " << vector << " was written to the file " << filepath << "!" << std::endl;
        system("pause");
    });
    this->menus.emplace(this->SaveKey, saveVectorMenu);
}

void MainMenu::CreatePrintMenu() {
    Menu* printAllMenu = new Menu("Print all", [](Menu&) {
        VectorDictionary& vectorDictionary = VectorDictionary::GetInstance();
        std::cout << vectorDictionary << std::endl;
        system("pause");
    });
    this->menus.emplace(this->PrintKey, printAllMenu);
}

void MainMenu::CreateQuitMenu() {
    Menu* quitMenu = new Menu("Quit", [this](Menu&) {
        this->SetCurrentMenu(nullptr);
    });
    this->menus.emplace(this->QuitKey, quitMenu);
}

void MainMenu::CreateMainMenu() {
    Menu* mainMenu = new Menu("Main Menu", nullptr);
    mainMenu
        ->addSubmenu(this->menus.at(this->AddKey))
        .addSubmenu(this->menus.at(this->OperationsKey))
        .addSubmenu(this->menus.at(this->SaveKey))
        .addSubmenu(this->menus.at(this->PrintKey))
        .addSubmenu(this->menus.at(this->QuitKey));

    this->menus.emplace(this->MainKey, mainMenu);
}

const std::string MainMenu::BackKey = "Back";
const std::string MainMenu::FromCLIKey = "CLI";
const std::string MainMenu::FromFileKey = "File";
const std::string MainMenu::FromExistKey = "Exist";
const std::string MainMenu::SumKey = "Sum";
const std::string MainMenu::DiffKey = "Diff";
const std::string MainMenu::MultKey = "Mult";
const std::string MainMenu::NormalizeKey = "Norm";
const std::string MainMenu::ScalarKey = "Scalar";
const std::string MainMenu::VectorKey = "Vector";
const std::string MainMenu::AddKey = "Add";
const std::string MainMenu::OperationsKey = "Operations";
const std::string MainMenu::SaveKey = "Save";
const std::string MainMenu::PrintKey = "Print";
const std::string MainMenu::QuitKey = "Quit";
const std::string MainMenu::MainKey = "Main";
