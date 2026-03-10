#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"
#include "balanced_lists.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

TEST_CASE("fillArray fills first n with 1 and next n with -1") {
    SUBCASE("n = 3 produces {1,1,1,-1,-1,-1}") {
        vector<int> arr;
        fillArray(arr, 3);
        CHECK(arr.size() == 6);
        for (int i = 0; i < 3; i++) CHECK(arr[i] == 1);
        for (int i = 3; i < 6; i++) CHECK(arr[i] == -1);
    }

    SUBCASE("n = 1 produces {1,-1}") {
        vector<int> arr;
        fillArray(arr, 1);
        CHECK(arr.size() == 2);
        CHECK(arr[0] == 1);
        CHECK(arr[1] == -1);
    }
}

TEST_CASE("Fisher-Yates Shuffle preserves array") {
    SUBCASE("Array length is preserved after shuffle") {
        vector<int> arr = {1, 1, -1, -1};
        int originalSize = arr.size();
        fisherYatesShuffle(arr);
        CHECK(arr.size() == originalSize);
    }

    SUBCASE("Elements are preserved after shuffle") {
        vector<int> arr = {1, 1, 1, -1, -1, -1};
        vector<int> sorted_original(arr);
        sort(sorted_original.begin(), sorted_original.end());

        fisherYatesShuffle(arr);

        vector<int> sorted_shuffled(arr);
        sort(sorted_shuffled.begin(), sorted_shuffled.end());

        CHECK(sorted_original == sorted_shuffled);
    }
}

TEST_CASE("Detect both negative and positive prefix sums") {
    SUBCASE("Sequence with both negative and positive prefix sums") {
        vector<int> arr = {1, -1, -1, 1}; 
        CHECK(hasBothNegativeAndPositivePrefixSums(arr));
    }

    SUBCASE("Well-balanced sequence has only non-negative prefix sums") {
        vector<int> arr = {1, 1, -1, -1}; 
        CHECK(!hasBothNegativeAndPositivePrefixSums(arr));
    }
}

TEST_CASE("Well-Balanced Sequence Detection") {
    SUBCASE("Simple well-balanced sequence: ()") {
        CHECK(isWellBalanced(vector<int>{1, -1}));
    }

    SUBCASE("Nested well-balanced sequence: (())") {
        CHECK(isWellBalanced(vector<int>{1, 1, -1, -1}));
    }

    SUBCASE("Multiple pairs: ()()") {
        CHECK(isWellBalanced(vector<int>{1, -1, 1, -1}));
    }
}

TEST_CASE("Proportion of well-balanced lists converges to 1/(n+1)") {
    srand(time(0));

    const int totalSimulations = 10000;
    vector<int> nValues = {3, 4, 5, 6, 7, 10};

    for (int n : nValues) {
        int wellBalancedCount = 0;
        int bothPrefixCount  = 0;

        for (int trial = 0; trial < totalSimulations; trial++) {
            vector<int> arr;
            fillArray(arr, n);
            fisherYatesShuffle(arr);

            if (hasBothNegativeAndPositivePrefixSums(arr)) {
                bothPrefixCount++;
                continue;  
            }

            if (isWellBalanced(arr)) {
                wellBalancedCount++;
            }
        }

        double proportion  = (double)wellBalancedCount / totalSimulations;
        double theoretical = 1.0 / (n + 1.0);

        cout << "\nn=" << n
             << " | well-balanced: " << wellBalancedCount
             << " | tossed out (both +/- prefix sums): " << bothPrefixCount
             << " | total: " << totalSimulations
             << " | proportion: " << fixed << setprecision(4) << proportion;

        CHECK(abs(proportion - theoretical) < 0.03);
    }
    cout << "\n";
}