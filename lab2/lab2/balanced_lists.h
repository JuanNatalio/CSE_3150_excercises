#ifndef BALANCED_LISTS_H
#define BALANCED_LISTS_H

#include <vector>

void fillArray(std::vector<int>& arr, int n);

void fisherYatesShuffle(std::vector<int>& arr);

bool hasBothNegativeAndPositivePrefixSums(const std::vector<int>& arr);

bool isWellBalanced(const std::vector<int>& arr);

std::vector<int> getPrefixSums(const std::vector<int>& arr);

#endif
