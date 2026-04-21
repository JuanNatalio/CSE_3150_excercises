#ifndef FRACTIONS_H
#define FRACTIONS_H

#include "bigint.h"
#include <utility>

using BigFraction = std::pair<bigint, bigint>;

bigint gcd(bigint a, bigint b);
bigint findCommonDenominator(BigFraction a, BigFraction b);
BigFraction simplifyFraction(BigFraction f);
BigFraction productOfTwoFractions(BigFraction a, BigFraction b);
BigFraction sumOfTwoFractions(BigFraction a, BigFraction b);

#endif
