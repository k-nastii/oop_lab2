#include "ConsoleUtilities/ConsoleUtilities.hpp"

#include <string>
#include <sstream>

std::string ConsoleUtilities::GetString(std::istream& in, const std::string& message) {
    std::print(std::cout, "{}: ", message);
    std::string result{};
    std::getline(in, result);

    return result;
}

int ConsoleUtilities::GetInt(std::istream& in, const std::string& message) {
    size_t index = std::numeric_limits<size_t>::max();
    std::string temp{};
    int result{};

    while (index != temp.size()) {
        std::print(std::cout, "{}: ", message);
        std::getline(in, temp);

        try {
            result = std::stoi(temp, &index);
        }
        catch (std::exception&) {
            index = std::numeric_limits<size_t>::max();
        }
    }

    return result;
}

double ConsoleUtilities::GetDouble(std::istream& in, const std::string& message) {
    size_t index = std::numeric_limits<size_t>::max();
    std::string temp{};
    double result{};

    while (index != temp.size()) {
        std::print(std::cout, "{}: ", message);
        std::getline(in, temp);

        try {
            result = std::stod(temp, &index);
        }
        catch (std::exception&) {
            index = std::numeric_limits<size_t>::max();
        }
    }

    return result;
}

lab::Vector ConsoleUtilities::GetVector(std::istream& in, const std::string& message) {
    lab::Vector vector{};
    std::string temp{};
    std::print(std::cout, "{}: ", message);
    std::getline(in, temp);
    std::stringstream ss(temp);
    ss >> vector;

    return vector;
}
