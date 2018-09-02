#include "BigInt.h"
#include <random>
#include <sstream>
#include <iostream>

BigInt::BigInt(const std::vector<uint8_t>& value) :
    mValue(value)
{
}

std::string BigInt::getString() const
{
    std::stringstream stream;

    bool isZero = true;

    // This looks super weird but (i >= 0) is always true for unsigned int.
    for (unsigned int i = mValue.size() - 1; i < mValue.size(); i--)
    {
        if (mValue[i] != 0 || !isZero || i == 0)
        {
            stream << std::dec << static_cast<int>(mValue[i]);
            isZero = false;
        }
    }

    return stream.str();
}

BigInt BigInt::getRandom(unsigned int numDigits)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<uint8_t> distribution(0,9);

    std::vector<uint8_t> value;

    for (unsigned int i = 0; i < numDigits; ++i)
    {
        int temp = distribution(generator);
        //std::cout << std::dec << static_cast<int>(temp);
        value.push_back(static_cast<uint8_t>(temp));
    }

    return BigInt(value);
}

BigInt BigInt::operator+(const BigInt& other) const
{
    std::vector<uint8_t> value;
    unsigned int maxSize = std::max(mValue.size(), other.mValue.size());

    uint8_t carryOver = 0;

    for (unsigned int i = 0; i < maxSize; ++i)
    {
        uint8_t temp = carryOver;

        if (i < mValue.size())
        {
            temp += mValue[i];
        }

        if (i < other.mValue.size())
        {
            temp += other.mValue[i];
        }

        carryOver = temp / 10;
        temp %= 10;

        value.push_back(temp);
    }

    if (carryOver > 0)
    {
        value.push_back(carryOver);
    }


    return BigInt(value);
}
