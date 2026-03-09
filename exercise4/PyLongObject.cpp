#include <iostream>

#include "PyLongObject.h"

PyLongObject::PyLongObject(long long _iValue)
{
    iValue = _iValue;
    fitsInLongLong = true;

    if (_iValue >= 0)
    {
        sign = 1;
    }
    else
    {
        sign = -1;
    }

    numDigits = 0;
    digitsBase30 = nullptr;
}

PyLongObject::PyLongObject(const PyLongObject &other)
{
    sign = other.sign;
    numDigits = other.numDigits;
    fitsInLongLong = other.fitsInLongLong;
    iValue = other.iValue;

    if (other.digitsBase30 != nullptr)
    {
        digitsBase30 = new unsigned[numDigits];
        for (int i = 0; i < numDigits; i++)
        {
            digitsBase30[i] = other.digitsBase30[i];
        }
    }
    else
    {
        digitsBase30 = nullptr;
    }
}

PyLongObject::~PyLongObject()
{
    if (digitsBase30 != nullptr)
    {
        delete[] digitsBase30;
    }
}

int PyLongObject::getDigitN(int n) const
{ // returns -1 on failure
    if (n > numDigits && !fitsInLongLong)
    {
        return -1;
    }
    else
    {
        return digitsBase30[n];
    }
}

long long PyLongObject::getSmallValue()
{
    if (fitsInLongLong)
    {
        return iValue;
    }
    else
    {
        return -1;
    }
}

bool PyLongObject::operator==(const PyLongObject &other) const
{
    if (this == &other)
    {
        return true;
    }
    else
    {
        if (fitsInLongLong != other.fitsInLongLong)
            return false;
        if (fitsInLongLong == other.fitsInLongLong && true == fitsInLongLong)
        {
            if (iValue == other.iValue)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (fitsInLongLong == other.fitsInLongLong && false == fitsInLongLong)
        {
            if (numDigits != other.numDigits)
            {
                return false;
            }
            else
            {
                for (int i = 0; i < numDigits; i++)
                {
                    if (getDigitN(i) != other.getDigitN(i))
                    {
                        return false;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

ostream &operator<<(ostream &os, const PyLongObject &pyLongObject)
{
    if (pyLongObject.fitsInLongLong)
    {
        os << pyLongObject.iValue;
    }
    else
    {
    }

    return os;
};

PyLongObject PyLongObject::operator+(const PyLongObject &other) const
{
    // STEP 1: Define our base (2^30 = 1,073,741,824)
    const unsigned long long BASE = 1ULL << 30;

    // STEP 2: Try simple addition first (both numbers fit in long long)
    if (this->fitsInLongLong && other.fitsInLongLong)
    {
        long long result = this->iValue + other.iValue;

        // STEP 3: Check if overflow occurred
        bool positiveOverflow = (this->iValue > 0 && other.iValue > 0 && result <= 0);
        bool negativeOverflow = (this->iValue < 0 && other.iValue < 0 && result >= 0);

        if (!positiveOverflow && !negativeOverflow)
        {
            return PyLongObject(result);
        }
    }

    // STEP 4: We need base-2^30 digit arithmetic
    // STEP 5: Convert first number to base-2^30 digits
    unsigned *digits1;
    int numDigits1;

    if (this->fitsInLongLong)
    {
        unsigned long long absValue = (this->iValue >= 0) ? this->iValue : -(this->iValue);

        unsigned temp[3];
        numDigits1 = 0;

        if (absValue == 0)
        {
            temp[0] = 0;
            numDigits1 = 1;
        }
        else
        {
            while (absValue > 0)
            {
                temp[numDigits1] = absValue % BASE;
                absValue = absValue / BASE;
                numDigits1++;
            }
        }

        digits1 = new unsigned[numDigits1];
        for (int i = 0; i < numDigits1; i++)
        {
            digits1[i] = temp[i];
        }
    }
    else
    {
        numDigits1 = this->numDigits;
        digits1 = new unsigned[numDigits1];
        for (int i = 0; i < numDigits1; i++)
        {
            digits1[i] = this->digitsBase30[i];
        }
    }

    // STEP 6: Convert second number to base-2^30 digits
    unsigned *digits2;
    int numDigits2;

    if (other.fitsInLongLong)
    {
        unsigned long long absValue = (other.iValue >= 0) ? other.iValue : -(other.iValue);
        unsigned temp[3];
        numDigits2 = 0;

        if (absValue == 0)
        {
            temp[0] = 0;
            numDigits2 = 1;
        }
        else
        {
            while (absValue > 0)
            {
                temp[numDigits2] = absValue % BASE;
                absValue = absValue / BASE;
                numDigits2++;
            }
        }

        digits2 = new unsigned[numDigits2];
        for (int i = 0; i < numDigits2; i++)
        {
            digits2[i] = temp[i];
        }
    }
    else
    {
        numDigits2 = other.numDigits;
        digits2 = new unsigned[numDigits2];
        for (int i = 0; i < numDigits2; i++)
        {
            digits2[i] = other.digitsBase30[i];
        }
    }

    // STEP 7: Perform base-2^30 addition with carrying
    int maxDigits = (numDigits1 > numDigits2) ? numDigits1 : numDigits2;
    int resultNumDigits = maxDigits + 1;
    unsigned *resultDigits = new unsigned[resultNumDigits];

    unsigned long long carry = 0;

    for (int i = 0; i < resultNumDigits; i++)
    {
        unsigned long long sum = carry;

        if (i < numDigits1)
        {
            sum += digits1[i];
        }

        if (i < numDigits2)
        {
            sum += digits2[i];
        }

        resultDigits[i] = sum % BASE;

        carry = sum / BASE;
    }

    // STEP 8: Remove leading zeros
    while (resultNumDigits > 1 && resultDigits[resultNumDigits - 1] == 0)
    {
        resultNumDigits--;
    }

    // STEP 9: Create result object
    PyLongObject result(0);
    result.fitsInLongLong = false;
    result.numDigits = resultNumDigits;
    result.digitsBase30 = new unsigned[resultNumDigits];

    for (int i = 0; i < resultNumDigits; i++)
    {
        result.digitsBase30[i] = resultDigits[i];
    }

    result.sign = 1;

    // STEP 10: Clean up temporary arrays
    delete[] digits1;
    delete[] digits2;
    delete[] resultDigits;

    return result;
}
