#include "balanced_lists.h"
#include <cstdlib>
#include <vector>

using namespace std;

void fillArray(vector<int>& arr, int n) {
    arr.resize(2 * n);
    for (int i = 0; i < n; i++) arr[i] = 1;
    for (int i = n; i < 2 * n; i++) arr[i] = -1;
}

void fisherYatesShuffle(vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

bool isWellBalanced(const vector<int>& arr) {
    int prefixSum = 0;
    for (int val : arr) {
        prefixSum += val;
        if (prefixSum < 0) {
            return false;
        }
    }
    return prefixSum == 0;
}

vector<int> getPrefixSums(const vector<int>& arr) {
    vector<int> prefixSums;
    int sum = 0;
    for (int val : arr) {
        sum += val;
        prefixSums.push_back(sum);
    }
    return prefixSums;
}

bool hasBothNegativeAndPositivePrefixSums(const vector<int>& arr) {
    int prefixSum = 0;
    bool hasNegative = false;
    bool hasPositive = false;
    for (int val : arr) {
        prefixSum += val;
        if (prefixSum < 0) hasNegative = true;
        if (prefixSum > 0) hasPositive = true;
    }
    return hasNegative && hasPositive;
}
