#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../include/doctest.h"
#include "helpers.h"

#include <cmath>

TEST_CASE("Magnitude of the zero vector is zero")
{
    CHECK(calculateVectorMagnitude({0.0, 0.0, 0.0}) == doctest::Approx(0.0));
}

TEST_CASE("Magnitude of a 3-4-5 vector is five")
{
    CHECK(calculateVectorMagnitude({3.0, 4.0}) == doctest::Approx(5.0));
}

TEST_CASE("Magnitude ignores sign of components")
{
    CHECK(calculateVectorMagnitude({-3.0, -4.0}) == doctest::Approx(5.0));
}

TEST_CASE("Magnitude of a mixed 3D vector")
{
    CHECK(calculateVectorMagnitude({1.0, 2.0, 2.0}) == doctest::Approx(3.0));
}

TEST_CASE("Dot product of orthogonal vectors is zero")
{
    CHECK(calculateVectorDotProduct({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}) == doctest::Approx(0.0));
}

TEST_CASE("Dot product of identical vectors equals sum of squares")
{
    CHECK(calculateVectorDotProduct({1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}) == doctest::Approx(14.0));
}

TEST_CASE("Dot product of mixed-sign vectors is computed correctly")
{
    CHECK(calculateVectorDotProduct({2.0, -1.0, 3.0}, {-4.0, 5.0, 1.0}) == doctest::Approx(-10.0));
}

TEST_CASE("Alpha for identical vectors is zero")
{
    double magnitude = calculateVectorMagnitude({2.0, 2.0});
    double dotProduct = calculateVectorDotProduct({2.0, 2.0}, {2.0, 2.0});
    CHECK(getAlpha(dotProduct, magnitude, magnitude) == doctest::Approx(0.0));
}

TEST_CASE("Alpha for orthogonal vectors is pi over two")
{
    double leftMagnitude = calculateVectorMagnitude({1.0, 0.0});
    double rightMagnitude = calculateVectorMagnitude({0.0, 1.0});
    double dotProduct = calculateVectorDotProduct({1.0, 0.0}, {0.0, 1.0});
    CHECK(getAlpha(dotProduct, leftMagnitude, rightMagnitude) == doctest::Approx(std::acos(-1.0) / 2.0));
}

TEST_CASE("Alpha for opposite vectors is pi")
{
    double leftMagnitude = calculateVectorMagnitude({1.0, 0.0});
    double rightMagnitude = calculateVectorMagnitude({-1.0, 0.0});
    double dotProduct = calculateVectorDotProduct({1.0, 0.0}, {-1.0, 0.0});
    CHECK(getAlpha(dotProduct, leftMagnitude, rightMagnitude) == doctest::Approx(std::acos(-1.0)));
}
