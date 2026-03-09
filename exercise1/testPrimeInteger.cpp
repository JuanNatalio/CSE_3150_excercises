#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 

#include "../include/doctest.h" 
#include "isPrimeFunction.h"

TEST_CASE("Testing isPrime function") {
    CHECK(isPrime(2) == true);
    CHECK(isPrime(3) == true);
    CHECK(isPrime(4) == false);
    CHECK(isPrime(5) == true);
    CHECK(isPrime(10) == false);
    CHECK(isPrime(13) == true);
    CHECK(isPrime(25) == false);
    CHECK(isPrime(29) == true);
    CHECK(isPrime(1) == false);
    CHECK(isPrime(0) == false);
    CHECK(isPrime(-7) == false);
}