#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../include/doctest.h"
#include "PyLongObject.h"
#include <climits>

TEST_CASE("Constructor - creates object with zero")
{
  PyLongObject zero(0);

  CHECK(zero.getSmallValue() == 0);
  CHECK(zero.fitsInLongLong == true);
  CHECK(zero.sign == 1);
  CHECK(zero.numDigits == 0);
  CHECK(zero.digitsBase30 == nullptr);
}

TEST_CASE("Constructor - creates object with positive number")
{
  PyLongObject positive(12345);

  CHECK(positive.getSmallValue() == 12345);
  CHECK(positive.fitsInLongLong == true);
  CHECK(positive.sign == 1);
  CHECK(positive.numDigits == 0);
  CHECK(positive.digitsBase30 == nullptr);
}

TEST_CASE("Constructor - creates object with negative number")
{
  PyLongObject negative(-9876);

  CHECK(negative.getSmallValue() == -9876);
  CHECK(negative.fitsInLongLong == true);
  CHECK(negative.sign == -1);
  CHECK(negative.numDigits == 0);
  CHECK(negative.digitsBase30 == nullptr);
}

TEST_CASE("Constructor - creates object with LLONG_MAX")
{
  PyLongObject maxVal(LLONG_MAX);

  CHECK(maxVal.getSmallValue() == LLONG_MAX);
  CHECK(maxVal.fitsInLongLong == true);
  CHECK(maxVal.sign == 1);
}

TEST_CASE("Constructor - creates object with LLONG_MIN")
{
  PyLongObject minVal(LLONG_MIN);

  CHECK(minVal.getSmallValue() == LLONG_MIN);
  CHECK(minVal.fitsInLongLong == true);
  CHECK(minVal.sign == -1);
}

TEST_CASE("Copy Constructor - copies simple value")
{
  PyLongObject original(42);
  PyLongObject copy(original);

  CHECK(copy.getSmallValue() == 42);
  CHECK(copy.fitsInLongLong == true);
  CHECK(copy.sign == original.sign);
  CHECK(copy == original);
}

TEST_CASE("Copy Constructor - creates independent copy")
{
  PyLongObject original(100);
  PyLongObject copy(original);

  CHECK(copy == original);

  CHECK(&copy != &original);
}

TEST_CASE("Equality - same values are equal")
{
  PyLongObject a(500);
  PyLongObject b(500);

  CHECK(a == b);
}

TEST_CASE("Equality - different values are not equal")
{
  PyLongObject a(100);
  PyLongObject b(200);

  CHECK_FALSE(a == b);
}

TEST_CASE("Equality - object equals itself")
{
  PyLongObject a(777);

  CHECK(a == a);
}

TEST_CASE("Addition - positive + positive (small)")
{
  PyLongObject a(100);
  PyLongObject b(250);
  PyLongObject result = a + b;

  CHECK(result.getSmallValue() == 350);
  CHECK(result.fitsInLongLong == true);
}

TEST_CASE("Addition - zero + zero")
{
  PyLongObject a(0);
  PyLongObject b(0);
  PyLongObject result = a + b;

  CHECK(result.getSmallValue() == 0);
}

TEST_CASE("Addition - number + zero")
{
  PyLongObject a(1000);
  PyLongObject b(0);
  PyLongObject result = a + b;

  CHECK(result.getSmallValue() == 1000);
}

TEST_CASE("Addition - large positive numbers (no overflow)")
{
  PyLongObject a(1000000000);
  PyLongObject b(2000000000);
  PyLongObject result = a + b;

  CHECK(result.getSmallValue() == 3000000000LL);
}

TEST_CASE("Addition - negative + negative")
{
  PyLongObject a(-100);
  PyLongObject b(-200);
  PyLongObject result = a + b;

  CHECK(result.getSmallValue() == -300);
}

TEST_CASE("Addition - positive + negative")
{
  PyLongObject a(500);
  PyLongObject b(-200);
  PyLongObject result = a + b;

  CHECK(result.getSmallValue() == 300);
}

TEST_CASE("Addition - positive overflow triggers base-2^30")
{
  PyLongObject a(LLONG_MAX);
  PyLongObject b(1000);
  PyLongObject result = a + b;

  CHECK(result.fitsInLongLong == false);
  CHECK(result.numDigits > 0);
  CHECK(result.digitsBase30 != nullptr);
}

TEST_CASE("Addition - large numbers requiring base-2^30")
{
  PyLongObject a(LLONG_MAX - 100);
  PyLongObject b(LLONG_MAX - 100);
  PyLongObject result = a + b;

  CHECK(result.fitsInLongLong == false);
  CHECK(result.numDigits > 0);
}

TEST_CASE("getSmallValue - returns correct value when fits")
{
  PyLongObject a(999);

  CHECK(a.getSmallValue() == 999);
}

TEST_CASE("getSmallValue - returns -1 when doesn't fit")
{
  PyLongObject a(LLONG_MAX);
  PyLongObject b(1000);
  PyLongObject result = a + b;

  if (!result.fitsInLongLong)
  {
    CHECK(result.getSmallValue() == -1);
  }
}

TEST_CASE("Addition - sequence of additions")
{
  PyLongObject a(10);
  PyLongObject b(20);
  PyLongObject c(30);

  PyLongObject result1 = a + b;
  PyLongObject result2 = result1 + c;

  CHECK(result2.getSmallValue() == 60);
}

TEST_CASE("Addition - adding to self")
{
  PyLongObject a(50);
  PyLongObject result = a + a;

  CHECK(result.getSmallValue() == 100);
}
