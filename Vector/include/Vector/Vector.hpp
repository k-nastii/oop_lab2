#pragma once
#include <vector>
#include <iostream>

namespace lab {
    class Vector {
    public:
        Vector() = default;
        Vector(const std::vector<double>&);
        Vector(size_t);
        Vector(const Vector&) = default;
        Vector(Vector&&) = default;

        ~Vector() = default;

        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) = default;

        double CalculateLength() const;
        double Dot(const Vector&) const;
        Vector Cross(const Vector&) const;

        Vector Sum(const Vector&) const;
        Vector Diff(const Vector&) const;
        Vector Mult(double) const;
        Vector Div(double) const;
        Vector Normalize() const;
        Vector Negate() const;
        double Angle(const Vector&) const;

        double At(size_t) const;
        double& At(size_t);

        long long GetDimentionsCount() const;

        bool IsColinear(const Vector&) const;
        bool IsOrtho(const Vector&) const;

        friend Vector operator+(const Vector&, const Vector&);
        friend Vector operator-(const Vector&, const Vector&);
        friend Vector operator+(const Vector&);
        friend Vector operator-(const Vector&);
        friend Vector operator*(const Vector&, double);
        friend Vector operator*(double, const Vector&);
        friend Vector operator/(const Vector&, double);
        friend Vector operator~(const Vector&);
        double operator[](size_t) const;
        double& operator[](size_t);

        Vector operator()(size_t, size_t) const;

        friend bool operator==(const Vector&, const Vector&);
        friend bool operator!=(const Vector&, const Vector&);
        friend bool operator<(const Vector&, const Vector&);
        friend bool operator<=(const Vector&, const Vector&);
        friend bool operator>(const Vector&, const Vector&);
        friend bool operator>=(const Vector&, const Vector&);

        friend std::ostream& operator<<(std::ostream&, const Vector&);
        friend std::istream& operator>>(std::istream&, Vector&);

    private:
        std::vector<double> data{};
    };
}
