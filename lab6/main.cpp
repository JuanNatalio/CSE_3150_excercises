#include <iostream>
#include <chrono>
#include <climits>
#include "fractions.cpp"

const int ITERATIONS = 100000;

template <typename T>
std::pair<T, T> intProduct(std::pair<T, T> a, std::pair<T, T> b) {
    return {a.first * b.first, a.second * b.second};
}

template <typename T>
std::pair<T, T> intSum(std::pair<T, T> a, std::pair<T, T> b) {
    return {a.first * b.second + b.first * a.second, a.second * b.second};
}

int main() {
    // --- int timing ---
    {
        std::pair<int, int> a = {3, 4};
        std::pair<int, int> b = {5, 7};
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            intProduct(a, b);
            intSum(a, b);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "int        : " << us << " microseconds\n";
    }

    // --- long long timing ---
    {
        std::pair<long long, long long> a = {3LL, 4LL};
        std::pair<long long, long long> b = {5LL, 7LL};
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            intProduct(a, b);
            intSum(a, b);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "long long  : " << us << " microseconds\n";
    }

    // --- bigint timing ---
    {
        BigFraction a = {bigint("3"), bigint("4")};
        BigFraction b = {bigint("5"), bigint("7")};
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            productOfTwoFractions(a, b);
            sumOfTwoFractions(a, b);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "bigint     : " << us << " microseconds\n";
    }

    // --- show where int fails (overflow) ---
    std::cout << "\n--- Overflow Demo ---\n";

    // INT_MAX = 2147483647; multiplying large fractions overflows int
    std::pair<int, int> big_a = {INT_MAX / 2, 3};
    std::pair<int, int> big_b = {INT_MAX / 2, 5};
    auto bad = intProduct(big_a, big_b);
    std::cout << "int product numerator (overflowed): " << bad.first << "\n";

    BigFraction ba = {bigint(std::to_string(INT_MAX / 2)), bigint("3")};
    BigFraction bb = {bigint(std::to_string(INT_MAX / 2)), bigint("5")};
    auto good = productOfTwoFractions(ba, bb);
    std::cout << "bigint product numerator (correct): " << good.first << "\n";

    return 0;
}
