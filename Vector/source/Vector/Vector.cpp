#include "Vector/Vector.hpp"

#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <format>
#include <iostream>
#include <print>

namespace lab {
    Vector::Vector(const std::vector<double>& data) : data(data) {
        // if (data.empty()) {
        //     throw std::runtime_error("Empty vector can't be created!");
        // }
    }
    
    Vector::Vector(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            data.push_back(0.0);
        }
    }

    Vector Vector::operator()(size_t head, size_t tail) const {
        Vector result = 0;

        if (head <= tail) { 
            result = Vector(tail - head + 1);

            for (size_t i = 0; i < result.GetDimentionsCount(); ++i) {
               result[i] = data[head + i];
            }
        }
        else {
            result = Vector(head - tail + 1);
            for (size_t i = 0; i < result.GetDimentionsCount(); ++i) {
                result[i] = data[head - i];
            }
        }
        
        return result;
    }

    // Vector& Vector::operator->() {
    //     return *this;
    // }

    double Vector::CalculateLength() const {
        double sum = 0.0;
        for (double x : this->data) {
            sum += x * x;
        }

        return pow(sum, 0.5);
    }

    double Vector::Dot(const Vector& another) const {
        const size_t minSize = std::min(this->GetDimentionsCount(), another.GetDimentionsCount());
        double result = 0.0;
        for (size_t i = 0; i < minSize; ++i) {
            result += this->data[i] * another.data[i];
        }

        return result;
    }

    Vector Vector::Cross(const Vector& vector) const {
        if (this->GetDimentionsCount() > 3 || vector.GetDimentionsCount() > 3) {
            throw std::runtime_error(std::format("Bad vector's count: got {}, need {}!", this->data.size(), this->GetDimentionsCount() + 2));
        }

        const double x1 = this->At(0);
        const double y1 = this->GetDimentionsCount() < 2 ? 0.0 : this->At(1);
        const double z1 = this->GetDimentionsCount() < 3 ? 0.0 : this->At(2);

        const double x2 = vector.At(0);
        const double y2 = vector.GetDimentionsCount() < 2 ? 0.0 : vector.At(1);
        const double z2 = vector.GetDimentionsCount() < 3 ? 0.0 : vector.At(2);

        const double i = y1 * z2 - z1 * y2;
        const double j = z1 * x2 - x1 * z2;
        const double k = x1 * y2 - y1 * x2;

        return Vector({i, j, k});
    }

    Vector Vector::Sum(const Vector& another) const {
        Vector result = *this;
        const Vector* minVector = &another;
        if (this->GetDimentionsCount() < another.GetDimentionsCount()) {
            result = another;
            minVector = this;
        }

        for (size_t i = 0; i < minVector->GetDimentionsCount(); ++i) {
            result.data[i] += minVector->data[i];
        }

        return result;
    }

    Vector Vector::Diff(const Vector& another) const {
        return Sum(another.Negate());
    }

    Vector Vector::Mult(double scalar) const {
        Vector result = *this;
        for (size_t i = 0; i < this->GetDimentionsCount(); ++i) {
            result.data[i] *= scalar;
        }

        return result;
    }

    Vector Vector::Div(double scalar) const {
        if (scalar == 0.0) {
            throw std::runtime_error("Division by zero!");
        }

        return Mult(1.0 / scalar);
    }

    Vector Vector::Normalize() const {
        if (this->CalculateLength() == 0.0) {
            return *this;
        }

        return Div(this->CalculateLength());
    }

    Vector Vector::Negate() const {
        Vector result = *this;
        for (size_t i = 0; i < result.GetDimentionsCount(); ++i) {
            result.data[i] *= -1;
        }

        return result;
    }

    double Vector::Angle(const Vector& vector) const {
        //  alpha = arccos((x1 * y2 - x2 * y1) / (| a | | b |))
        const double dot = this->Dot(vector);
        const double firstLength = this->CalculateLength();
        const double secondLength = vector.CalculateLength();

        if (firstLength == 0.0 || secondLength == 0.0) {
            throw std::runtime_error("Angle between vectors is not defined!");
        }

        return acos(dot / firstLength / secondLength);
    }

    double Vector::At(size_t index) const {
        if (index >= this->GetDimentionsCount()) {
            throw std::runtime_error(std::format("Index {} out of bounds, size {}", index, this->data.size()));
        }

        return this->data[index];
    }

    double& Vector::At(size_t index) {
        if (index >= this->GetDimentionsCount()) {
            throw std::runtime_error(std::format("Index {} out of bounds, size {}", index, this->data.size()));
        }

        return this->data[index];
    }

    long long Vector::GetDimentionsCount() const {
        // return this->data.size();
        return std::ssize(this->data);
    }

    bool Vector::IsColinear(const Vector& vector) const {
        return abs(cos(this->Angle(vector))) == 1.0;
    }

    bool Vector::IsOrtho(const Vector& vector) const {
        return cos(this->Angle(vector)) == 0.0;
    }

    Vector operator+(const Vector& first, const Vector& second) {
        return first.Sum(second);
    }

    Vector operator-(const Vector& first, const Vector& second) {
        return first.Diff(second);
    }
    
    Vector operator+(const Vector& vector) {
        return vector;
    }

    Vector operator-(const Vector& vector) {
        return vector.Negate();
    }

    Vector operator*(const Vector& vector, double scalar) {
        return vector.Mult(scalar);
    }

    Vector operator*(double scalar, const Vector& vector) {
        return vector * scalar;
    }

    Vector operator/(const Vector& vector, double scalar) {
        return vector.Div(scalar);
    }

    Vector operator~(const Vector& vector) {
        return vector.Normalize();
    }

   double Vector::operator[](size_t index) const {
        return this->At(index);
    }

    double& Vector::operator[](size_t index) {
        return this->At(index);
    }

    bool operator==(const Vector& first, const Vector& second) {
        // const auto [minSize, maxSize] = std::minmax(
        //     first.GetDimentionsCount(),
        //     second.GetDimentionsCount()
        // );
        const size_t minSize = first.GetDimentionsCount() < second.GetDimentionsCount() ?
            first.GetDimentionsCount() :
            second.GetDimentionsCount();

        const size_t maxSize = first.GetDimentionsCount() > second.GetDimentionsCount() ?
            first.GetDimentionsCount() :
            second.GetDimentionsCount();

        const Vector& maxVector = first.GetDimentionsCount() > second.GetDimentionsCount() ?
            first :
            second;

        for (size_t i = 0; i < minSize; ++i) {
            if (first[i] != second[i]) {
                return false;
            }
        }

        for (size_t i = minSize; i < maxSize; ++i) {
            if (maxVector[i] != 0.0) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector& first, const Vector& second) {
        return !(first == second);
    }

    bool operator<(const Vector& first, const Vector& second) {
        const double firstLength = first.CalculateLength();
        const double secondLength = second.CalculateLength();

        if (firstLength == secondLength) {
            // const auto [minSize, maxSize] = std::minmax(
            //     first.GetDimentionsCount(),
            //     second.GetDimentionsCount()
            // );
            const size_t minSize = first.GetDimentionsCount() < second.GetDimentionsCount() ?
                first.GetDimentionsCount() :
                second.GetDimentionsCount();

            const size_t maxSize = first.GetDimentionsCount() > second.GetDimentionsCount() ?
                first.GetDimentionsCount() :
                second.GetDimentionsCount();
    
            const Vector& maxVector = first.GetDimentionsCount() > second.GetDimentionsCount() ?
                first :
                second;
    
            for (size_t i = 0; i < minSize; ++i) {
                if (first[i] == second[i]) {
                    continue;
                }

                return first[i] < second[i];
            }
    
            for (size_t i = minSize; i < maxSize; ++i) {
                if (maxVector[i] == 0.0) {
                    continue;
                }

                return maxVector[i] < 0.0;
            }
    
            return false;
        }
        
        return firstLength < secondLength;
    }

    bool operator>(const Vector& first, const Vector& second) {
        return second < first;
    }

    bool operator<=(const Vector& first, const Vector& second) {
        return first < second || first == second;
    }

    bool operator>=(const Vector& first, const Vector& second) {
        return first > second || first == second;
    }

    std::ostream& operator<<(std::ostream& out, const Vector& vector) {
        out << "{";
        for (long long i = 0; i < vector.GetDimentionsCount(); ++i) {
            out << vector[i];
            if (i != vector.GetDimentionsCount() - 1) {
                out << ", ";
            }
        }

        return out << "}";
    }

    std::istream& operator>>(std::istream& in, Vector& vector) {
        char symbol{};
        in >> symbol;
        if (symbol != '{') {
            // in.setstate(std::ios::failbit);
            return in;
        }

        for (;;) {
            double temp{};
            if (!(in >> temp)) {
                if (in.peek() == ',') {
                    // in.setstate(std::ios::failbit);
                    return in;
                }

                break;
            }
            else {
                vector.data.push_back(temp);
                in >> symbol;
                if (symbol != ',') {
                    // in.setstate(std::ios::failbit);
                    return in;
                }
            }
        }

        if (symbol != '}') {
            // in.setstate(std::ios::failbit);
            return in;
        }

        return in;
    }
}
