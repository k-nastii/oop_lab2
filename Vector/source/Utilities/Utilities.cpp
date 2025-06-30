#include <iostream>
#include <print>

void Test(int) {
    std::println(std::cout, "TEST!");
}

double ScalarProduct(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}
