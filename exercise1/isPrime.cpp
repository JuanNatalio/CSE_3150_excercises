#include <iostream>
#include "isPrimeFunction.h"

using namespace std;

int main () {
    int testValue;

    cout << "Enter an Intenger: " << endl;

    cin >> testValue;

    if (isPrime(testValue)) {
        cout << testValue << " is a prime number." << endl;
    } else {
        cout << testValue << " is not a prime number." << endl;
    }

}