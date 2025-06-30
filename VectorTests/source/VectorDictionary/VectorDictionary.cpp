#include "Vector/Vector.hpp"
#include "VectorDictionary/VectorDictionary.hpp"

VectorDictionary::~VectorDictionary() {
    for (auto& [_, value] : this->nameToVectorMap) {
        delete value;
    }
}

VectorDictionary& VectorDictionary::GetInstance() {
    static VectorDictionary instance{};
    return instance;
}

bool VectorDictionary::Contains(const std::string& key, const std::string& errorMessage) {
    if (this->nameToVectorMap.contains(key)) {
        return true;
    }
    std::println(std::cout, "{}", errorMessage);
    return false;
}

const lab::Vector& VectorDictionary::operator[](const std::string& key) const {
    return *this->nameToVectorMap.at(key);
}

lab::Vector& VectorDictionary::operator[](const std::string& key) {
   
   return *this->nameToVectorMap.at(key);
}

void VectorDictionary::Add(const std::string& key, const lab::Vector& vector) {
    if (this->nameToVectorMap.contains(key)) {
        (*this)[key] = vector;
    }
    else {
        this->nameToVectorMap.emplace(key, new lab::Vector(vector));
    }
}

void VectorDictionary::Remove(const std::string& key, const std::string& errorMessage) {
    if (this->nameToVectorMap.contains(key)) {
        this->nameToVectorMap.erase(key);
    }
    else {
        std::println(std::cout, "{}", errorMessage);
    }
}

std::ostream& operator<<(std::ostream& out, const VectorDictionary& vectorDictionary) {
    for (const auto& [key, value] : vectorDictionary.nameToVectorMap) {
        out << "[\"" << key << "\"] = " << *value << "\n";
    }
    return out;
}