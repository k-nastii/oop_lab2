#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Menu/Menu.hpp"
#include "Vector/Vector.hpp"

class VectorDictionary {
public:
    VectorDictionary(const VectorDictionary&) = delete;
    VectorDictionary(VectorDictionary&&) = default;
    VectorDictionary& operator=(const VectorDictionary&) = delete;
    VectorDictionary& operator=(VectorDictionary&&) = default;
    ~VectorDictionary();

    static VectorDictionary& GetInstance();

    bool Contains(const std::string& key, const std::string& errorMessage);
    const lab::Vector& operator[](const std::string& key) const;
    lab::Vector& operator[](const std::string& key);
    void Add(const std::string& key, const lab::Vector& vector);
    void Remove(const std::string& key, const std::string& errorMessage);

    friend std::ostream& operator<<(std::ostream& out, const VectorDictionary& vectorDictionary);

private:
    VectorDictionary() = default;
    std::unordered_map<std::string, lab::Vector*> nameToVectorMap;
};
