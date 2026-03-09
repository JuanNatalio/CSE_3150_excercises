#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../include/doctest.h"
#include "ComplexArray.h"
#include "Complex.h"
#include <utility> // for std::move

TEST_CASE("Default constructor creates empty array")
{
    ComplexArray arr;
    CHECK(arr.getSize() == 0);
}

TEST_CASE("Constructor with size creates array of specified size")
{
    const int size = 5;
    ComplexArray arr(size);
    CHECK(arr.getSize() == size);
}

TEST_CASE("Can store and retrieve Complex numbers")
{
    ComplexArray arr(3);

    arr[0] = Complex(1.0, 2.0);
    arr[1] = Complex(3.5, 4.5);
    arr[2] = Complex(-1.0, -2.0);

    CHECK(arr[0].getReal() == 1.0);
    CHECK(arr[0].getImag() == 2.0);
    CHECK(arr[1].getReal() == 3.5);
    CHECK(arr[1].getImag() == 4.5);
    CHECK(arr[2].getReal() == -1.0);
    CHECK(arr[2].getImag() == -2.0);
}

TEST_CASE("Move constructor transfers ownership")
{
    ComplexArray source(3);
    source[0] = Complex(1.0, 2.0);
    source[1] = Complex(3.0, 4.0);
    source[2] = Complex(5.0, 6.0);

    ComplexArray destination(std::move(source));

    CHECK(destination.getSize() == 3);
    CHECK(destination[0].getReal() == 1.0);
    CHECK(destination[0].getImag() == 2.0);
    CHECK(destination[1].getReal() == 3.0);
    CHECK(destination[1].getImag() == 4.0);
    CHECK(destination[2].getReal() == 5.0);
    CHECK(destination[2].getImag() == 6.0);

    CHECK(source.getSize() == 0);
}

TEST_CASE("Move assignment operator transfers ownership")
{
    ComplexArray source(2);
    source[0] = Complex(7.0, 8.0);
    source[1] = Complex(9.0, 10.0);

    ComplexArray destination(1);
    destination[0] = Complex(99.0, 99.0);

    destination = std::move(source);

    CHECK(destination.getSize() == 2);
    CHECK(destination[0].getReal() == 7.0);
    CHECK(destination[0].getImag() == 8.0);
    CHECK(destination[1].getReal() == 9.0);
    CHECK(destination[1].getImag() == 10.0);

    CHECK(source.getSize() == 0);
}

TEST_CASE("Move assignment to self is safe")
{
    ComplexArray arr(2);
    arr[0] = Complex(1.0, 2.0);
    arr[1] = Complex(3.0, 4.0);

    arr = std::move(arr);

    CHECK(arr.getSize() == 2);
    CHECK(arr[0].getReal() == 1.0);
    CHECK(arr[1].getReal() == 3.0);
}

TEST_CASE("Array access with bounds checking")
{
    ComplexArray arr(2);
    arr[0] = Complex(1.0, 2.0);
    arr[1] = Complex(3.0, 4.0);

    CHECK_NOTHROW(arr[0]);
    CHECK_NOTHROW(arr[1]);

    CHECK_THROWS_AS(arr[-1], std::out_of_range);
    CHECK_THROWS_AS(arr[2], std::out_of_range);
    CHECK_THROWS_AS(arr[100], std::out_of_range);
}

TEST_CASE("Const array access works correctly")
{
    ComplexArray arr(2);
    arr[0] = Complex(5.0, 6.0);
    arr[1] = Complex(7.0, 8.0);

    const ComplexArray &constArr = arr;

    CHECK(constArr[0].getReal() == 5.0);
    CHECK(constArr[1].getImag() == 8.0);
}

ComplexArray createArrayWithData(int size)
{
    ComplexArray arr(size);
    for (int i = 0; i < size; i++)
    {
        arr[i] = Complex(i * 1.0, i * 2.0);
    }
    return arr;
}

TEST_CASE("Move constructor works when returning from function")
{
    ComplexArray result = createArrayWithData(4);

    CHECK(result.getSize() == 4);
    CHECK(result[0].getReal() == 0.0);
    CHECK(result[1].getReal() == 1.0);
    CHECK(result[2].getReal() == 2.0);
    CHECK(result[3].getReal() == 3.0);
}

TEST_CASE("No memory leaks - multiple moves")
{
    ComplexArray arr1(10);
    for (int i = 0; i < 10; i++)
    {
        arr1[i] = Complex(i * 1.0, i * 1.0);
    }

    ComplexArray arr2(std::move(arr1));
    ComplexArray arr3(std::move(arr2));
    ComplexArray arr4 = std::move(arr3);

    CHECK(arr4.getSize() == 10);
    CHECK(arr4[5].getReal() == 5.0);
}
