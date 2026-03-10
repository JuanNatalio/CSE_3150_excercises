#include "lab1.h"
#include <iostream>
#include <cstdio>

bool non_neg_prefix_sum (std::vector<int> numbers) {
    int prefix_sum = 0;
    for (int num : numbers) {
        prefix_sum += num;
        if (prefix_sum < 0) {
            return false;
        };
    }
    return true;
}

bool non_positive_prefix_sum (std::vector<int> numbers) {
    int prefix_sum = 0;
    for (int num : numbers) {
        prefix_sum += num;
        if (prefix_sum > 0) {
            return false;
        };
    }
    return true;
}
