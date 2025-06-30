#include <iostream>

#include "Vector/Vector.hpp"

class ConsoleUtilities {
public:
    ConsoleUtilities() = delete;
    ConsoleUtilities(const ConsoleUtilities&) = delete;
    ConsoleUtilities(ConsoleUtilities&&) = delete;

    ConsoleUtilities& operator=(const ConsoleUtilities&) = delete;
    ConsoleUtilities& operator=(ConsoleUtilities&&) = delete;

    ~ConsoleUtilities() = delete;

    static std::string GetString(std::istream& in, const std::string& message);
    static int GetInt(std::istream& in, const std::string& message);
    static double GetDouble(std::istream& in, const std::string& message);
    static lab::Vector GetVector(std::istream& in, const std::string& message);
};