#ifndef __ISPRIMEFUNCTION_H
#define __ISPRIMEFUNCTION_H

bool isPrime(int pTest) {
    bool isPrime = true;
    if (pTest <= 1) {
        return false;
    }

    for (int i = 2; i < pTest; i++) {
        if (pTest % i == 0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}

# endif