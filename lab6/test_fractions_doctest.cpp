#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../include/doctest.h"
#include "fractions.cpp"

static bool fracEqual(BigFraction a, BigFraction b) {
    return (a.first == b.first) && (a.second == b.second);
}

TEST_CASE("simplifyFraction reduces correctly") {
    CHECK(fracEqual(simplifyFraction({bigint("6"), bigint("8")}),   {bigint("3"), bigint("4")}));
    CHECK(fracEqual(simplifyFraction({bigint("10"), bigint("5")}),  {bigint("2"), bigint("1")}));
    CHECK(fracEqual(simplifyFraction({bigint("7"), bigint("11")}),  {bigint("7"), bigint("11")}));
}

TEST_CASE("productOfTwoFractions basic cases") {
    // (1/2) * (1/3) = 1/6
    CHECK(fracEqual(productOfTwoFractions({bigint("1"), bigint("2")}, {bigint("1"), bigint("3")}),
                    {bigint("1"), bigint("6")}));

    // (2/3) * (3/4) = 6/12 = 1/2
    CHECK(fracEqual(productOfTwoFractions({bigint("2"), bigint("3")}, {bigint("3"), bigint("4")}),
                    {bigint("1"), bigint("2")}));

    // (5/6) * (6/5) = 30/30 = 1/1
    CHECK(fracEqual(productOfTwoFractions({bigint("5"), bigint("6")}, {bigint("6"), bigint("5")}),
                    {bigint("1"), bigint("1")}));
}

TEST_CASE("sumOfTwoFractions basic cases") {
    // (1/2) + (1/3) = 5/6
    CHECK(fracEqual(sumOfTwoFractions({bigint("1"), bigint("2")}, {bigint("1"), bigint("3")}),
                    {bigint("5"), bigint("6")}));

    // (1/4) + (1/4) = 2/4 = 1/2
    CHECK(fracEqual(sumOfTwoFractions({bigint("1"), bigint("4")}, {bigint("1"), bigint("4")}),
                    {bigint("1"), bigint("2")}));

    // (2/5) + (3/5) = 5/5 = 1/1
    CHECK(fracEqual(sumOfTwoFractions({bigint("2"), bigint("5")}, {bigint("3"), bigint("5")}),
                    {bigint("1"), bigint("1")}));
}

TEST_CASE("productOfTwoFractions with large numbers that would overflow int") {
    // 3000000000 > INT_MAX; (3000000000/1) * (1/3) = 1000000000/1
    BigFraction a = {bigint("3000000000"), bigint("1")};
    BigFraction b = {bigint("1"), bigint("3")};
    BigFraction result = productOfTwoFractions(a, b);
    CHECK(fracEqual(result, {bigint("1000000000"), bigint("1")}));
}

TEST_CASE("sumOfTwoFractions with large numbers that would overflow int") {
    // (2000000000/3) + (1000000000/3) = 3000000000/3 = 1000000000/1
    BigFraction a = {bigint("2000000000"), bigint("3")};
    BigFraction b = {bigint("1000000000"), bigint("3")};
    BigFraction result = sumOfTwoFractions(a, b);
    CHECK(fracEqual(result, {bigint("1000000000"), bigint("1")}));
}
