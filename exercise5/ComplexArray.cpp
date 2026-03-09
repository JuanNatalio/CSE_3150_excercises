#include "ComplexArray.h"

ComplexArray::ComplexArray() : complexArray{nullptr}, size{0} {};
ComplexArray::ComplexArray(int _size) : complexArray{new Complex[_size]}, size{_size} {};

ComplexArray::ComplexArray(ComplexArray &&other) : complexArray{other.complexArray}, size{other.size}
{
    other.complexArray = nullptr;
    other.size = 0;
}

ComplexArray &ComplexArray::operator=(ComplexArray &&other)
{
    if (this != &other)
    {
        delete[] complexArray;

        complexArray = other.complexArray;
        size = other.size;

        other.complexArray = nullptr;
        other.size = 0;
    }
    return *this;
}

ComplexArray::~ComplexArray()
{
    delete[] complexArray;
}

Complex &ComplexArray::operator[](int index)
{
    if (index < 0 || index >= size)
    {
        throw out_of_range("Index out of range");
    }
    return complexArray[index];
}

const Complex &ComplexArray::operator[](int index) const
{
    if (index < 0 || index >= size)
    {
        throw out_of_range("Index out of range");
    }
    return complexArray[index];
}

int ComplexArray::getSize() const
{
    return size;
}