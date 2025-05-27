#include <iostream>
#include <unordered_map>
#include "Menu/Menu.hpp"

class Menu;

class MainMenu {
public:
    MainMenu(const MainMenu&) = delete;
    MainMenu(MainMenu&&) = delete;
    MainMenu& operator=(const MainMenu&) = delete;
    MainMenu& operator=(MainMenu&&) = delete;
    ~MainMenu();

    static MainMenu& GetInstance();

    Menu* GetCurrentMenu();
    void SetCurrentMenu(Menu* menu);

private:
    MainMenu();
    Menu* currentMenu{};
    std::unordered_map<std::string, Menu*> menus{};

    const static std::string BackKey;
    const static std::string FromCLIKey;
    const static std::string FromFileKey;
    const static std::string FromExistKey;
    const static std::string SumKey;
    const static std::string DiffKey;
    const static std::string MultKey;
    const static std::string NormalizeKey;
    const static std::string ScalarKey;
    const static std::string VectorKey;
    const static std::string AddKey;
    const static std::string OperationsKey;
    const static std::string SaveKey;
    const static std::string PrintKey;
    const static std::string QuitKey;
    const static std::string MainKey;

    void CreateMenus();
    void CreateBackMenu();
    void CreateFromCLIMenu();
    void CreateFromFileMenu();
    void CreateFromExistingMenu();
    void CreateSumMenu();
    void CreateDiffMenu();
    void CreateMultMenu();
    void CreateNormalizeMenu();
    void CreateScalarMenu();
    void CreateVectorMenu();
    void CreateAddMenu();
    void CreateOperationsMenu();
    void CreateSaveMenu();
    void CreatePrintMenu();
    void CreateQuitMenu();
    void CreateMainMenu();
};
