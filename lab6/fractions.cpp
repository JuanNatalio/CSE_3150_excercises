#include "fractions.h"

bigint gcd(bigint a, bigint b) {
    bigint zero("0");
    while (!(b == zero)) {
        bigint t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bigint findCommonDenominator(BigFraction a, BigFraction b) {
    return a.second * b.second;
}

BigFraction simplifyFraction(BigFraction f) {
    bigint g = gcd(f.first, f.second);
    return {f.first / g, f.second / g};
}

BigFraction productOfTwoFractions(BigFraction a, BigFraction b) {
    BigFraction result = {a.first * b.first, a.second * b.second};
    return simplifyFraction(result);
}

BigFraction sumOfTwoFractions(BigFraction a, BigFraction b) {
    bigint commonDenom = findCommonDenominator(a, b);
    bigint numerator = (a.first * b.second) + (b.first * a.second);
    return simplifyFraction({numerator, commonDenom});
}
