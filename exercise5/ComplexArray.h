#ifndef _COMPLEXARRAY_H_
#define _COMPLEXARRAY_H_

#include "Complex.h"
#include <iostream>

using namespace std;

class ComplexArray
{
    Complex *complexArray;
    int size;

public:
    ComplexArray();
    ComplexArray(int _size);

    // Delete copy constructor and copy assignment (no copying allowed)
    ComplexArray(const ComplexArray &complexArray) = delete;
    ComplexArray &operator=(const ComplexArray &complexArray) = delete;

    // Move constructor and move assignment operator
    ComplexArray(ComplexArray &&other);
    ComplexArray &operator=(ComplexArray &&other);

    ~ComplexArray();

    // Access elements
    Complex &operator[](int index);
    const Complex &operator[](int index) const;

    int getSize() const;
};

#endif