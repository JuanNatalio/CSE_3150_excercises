#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lab1.h"

TEST_CASE("non_neg_prefix_sum: Empty vector") {
    std::vector<int> numbers = {};
    CHECK(non_neg_prefix_sum(numbers) == true);
}

TEST_CASE("non_neg_prefix_sum: All 1s") {
    std::vector<int> numbers = {1, 1, 1, 1, 1};
    CHECK(non_neg_prefix_sum(numbers) == true);
}

TEST_CASE("non_neg_prefix_sum: All -1s") {
    std::vector<int> numbers = {-1, -1, -1, -1};
    CHECK(non_neg_prefix_sum(numbers) == false);
}

TEST_CASE("non_neg_prefix_sum: Single 1") {
    std::vector<int> numbers = {1};
    CHECK(non_neg_prefix_sum(numbers) == true);
}

TEST_CASE("non_neg_prefix_sum: Single -1") {
    std::vector<int> numbers = {-1};
    CHECK(non_neg_prefix_sum(numbers) == false);
}

TEST_CASE("non_neg_prefix_sum: Alternating 1, -1 starting with 1") {
    std::vector<int> numbers = {1, -1, 1, -1, 1, -1};
    CHECK(non_neg_prefix_sum(numbers) == true);
}

TEST_CASE("non_neg_prefix_sum: Alternating -1, 1 starting with -1") {
    std::vector<int> numbers = {-1, 1, -1, 1};
    CHECK(non_neg_prefix_sum(numbers) == false);
}

TEST_CASE("non_neg_prefix_sum: More 1s than -1s") {
    std::vector<int> numbers = {1, 1, -1, 1, -1};
    CHECK(non_neg_prefix_sum(numbers) == true);
}

TEST_CASE("non_neg_prefix_sum: Goes negative after starting positive") {
    std::vector<int> numbers = {1, -1, -1};
    CHECK(non_neg_prefix_sum(numbers) == false);
}

TEST_CASE("non_neg_prefix_sum: Long sequence staying non-negative") {
    std::vector<int> numbers = {1, 1, -1, 1, 1, -1, -1, 1};
    CHECK(non_neg_prefix_sum(numbers) == true);
}

TEST_CASE("non_neg_prefix_sum: Touches zero multiple times") {
    std::vector<int> numbers = {1, -1, 1, -1};
    CHECK(non_neg_prefix_sum(numbers) == true);
}

TEST_CASE("non_neg_prefix_sum: Two -1s after one 1") {
    std::vector<int> numbers = {1, -1, -1, 1};
    CHECK(non_neg_prefix_sum(numbers) == false);
}

TEST_CASE("non_positive_prefix_sum: Empty vector") {
    std::vector<int> numbers = {};
    CHECK(non_positive_prefix_sum(numbers) == true);
}

TEST_CASE("non_positive_prefix_sum: All -1s") {
    std::vector<int> numbers = {-1, -1, -1, -1, -1};
    CHECK(non_positive_prefix_sum(numbers) == true);
}

TEST_CASE("non_positive_prefix_sum: All 1s") {
    std::vector<int> numbers = {1, 1, 1, 1};
    CHECK(non_positive_prefix_sum(numbers) == false);
}

TEST_CASE("non_positive_prefix_sum: Single -1") {
    std::vector<int> numbers = {-1};
    CHECK(non_positive_prefix_sum(numbers) == true);
}

TEST_CASE("non_positive_prefix_sum: Single 1") {
    std::vector<int> numbers = {1};
    CHECK(non_positive_prefix_sum(numbers) == false);
}

TEST_CASE("non_positive_prefix_sum: Alternating -1, 1 starting with -1") {
    std::vector<int> numbers = {-1, 1, -1, 1, -1, 1};
    CHECK(non_positive_prefix_sum(numbers) == true);
}

TEST_CASE("non_positive_prefix_sum: Alternating 1, -1 starting with 1") {
    std::vector<int> numbers = {1, -1, 1, -1};
    CHECK(non_positive_prefix_sum(numbers) == false);
}

TEST_CASE("non_positive_prefix_sum: More -1s than 1s") {
    std::vector<int> numbers = {-1, -1, 1, -1, 1};
    CHECK(non_positive_prefix_sum(numbers) == true);
}

TEST_CASE("non_positive_prefix_sum: Goes positive after starting negative") {
    std::vector<int> numbers = {-1, 1, 1};
    CHECK(non_positive_prefix_sum(numbers) == false);
}

TEST_CASE("non_positive_prefix_sum: Long sequence staying non-positive") {
    std::vector<int> numbers = {-1, -1, 1, -1, -1, 1, 1, -1};
    CHECK(non_positive_prefix_sum(numbers) == true);
}

TEST_CASE("non_positive_prefix_sum: Touches zero multiple times") {
    std::vector<int> numbers = {-1, 1, -1, 1};
    CHECK(non_positive_prefix_sum(numbers) == true);
}

TEST_CASE("non_positive_prefix_sum: Two 1s after one -1") {
    std::vector<int> numbers = {-1, 1, 1, -1};
    CHECK(non_positive_prefix_sum(numbers) == false);
}
