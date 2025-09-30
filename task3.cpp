// CMP SCI 3780 — Project 1 (Task 3)
// Build with: g++ -std=c++17 -O2 -g -Wall -Wextra -pedantic task3.cpp -o task3
// Goal: Read two signed integers and perform +, *, / with *overflow-safe* checks
// without triggering UB or relying on overflow behavior.

#include <iostream>
#include <limits>
#include <optional>
#include <string>

using std::numeric_limits;

bool safe_add(int a, int b, int& out) {
    if (b > 0) {
        if (a > numeric_limits<int>::max() - b) return false;
    } else {
        if (a < numeric_limits<int>::min() - b) return false;
    }
    out = a + b;
    return true;
}

bool safe_mul(int a, int b, int& out) {
    // Handle zeros early
    if (a == 0 || b == 0) { out = 0; return true; }
    // Special case: INT_MIN * -1 overflows in 2's complement
    if ((a == numeric_limits<int>::min() && b == -1) ||
        (b == numeric_limits<int>::min() && a == -1)) {
        return false;
    }
    // General checks using division with sign
    // We check: |a| > INT_MAX / |b| => overflow
    long long aa = a < 0 ? -(long long)a : (long long)a;
    long long bb = b < 0 ? -(long long)b : (long long)b;
    if (aa > (long long)numeric_limits<int>::max() / bb) return false;

    out = a * b;
    return true;
}

bool safe_div(int a, int b, int& out) {
    if (b == 0) return false;
    if (a == numeric_limits<int>::min() && b == -1) return false; // overflow
    out = a / b;
    return true;
}

int main() {
    std::cout << "Enter two integers: ";
    int x, y;
    if (!(std::cin >> x >> y)) {
        std::cerr << "Input error.\n";
        return 1;
    }

    int sum, prod, quot;
    if (safe_add(x, y, sum)) {
        std::cout << x << " + " << y << " = " << sum << "\n";
    } else {
        std::cout << "Addition overflow detected for " << x << " + " << y << "\n";
    }

    if (safe_mul(x, y, prod)) {
        std::cout << x << " * " << y << " = " << prod << "\n";
    } else {
        std::cout << "Multiplication overflow detected for " << x << " * " << y << "\n";
    }

    if (safe_div(x, y, quot)) {
        std::cout << x << " / " << y << " = " << quot << "\n";
    } else {
        std::cout << "Division error (divide by zero or overflow) for " << x << " / " << y << "\n";
    }

    return 0;
}
