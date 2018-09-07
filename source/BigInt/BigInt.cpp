#include "BigInt.h"
#include <random>
#include <sstream>
#include <iostream>

BigInt::BigInt(const BigInt& other) :
    mIsPositive(other.mIsPositive),
    mValue(other.mValue)
{
    trim();
}

BigInt::BigInt(bool isPositive, const std::vector<uint8_t>& value) :
    mIsPositive(isPositive),
    mValue(value)
{
    trim();
}

BigInt::BigInt(int64_t value)
{
    if (value < 0)
    {
        mIsPositive = false;
    }
    else
    {
        mIsPositive = true;
    }

    std::vector<uint8_t> valueVector;
    int64_t tempValue = std::abs(value);
    while (tempValue > 0)
    {
        valueVector.push_back(tempValue % 10);
        tempValue /= 10;
    }

    mValue = valueVector;
}

void BigInt::trim()
{
    for (unsigned int i = mValue.size() - 1; i < mValue.size(); --i)
    {
        if (mValue[i] == 0)
        {
            mValue.pop_back();
        }
        else
        {
            break;
        }
    }
}

//=============================================================================**
// Gets the value as a signed integer
//=============================================================================**
int64_t BigInt::getIntValue() const
{
    int64_t value = 0;
    int64_t pow = 1;

    for (int i = 0; i < mValue.size(); ++i)
    {
        value += pow * mValue[i];
        pow *= 10;
    }

    if (!mIsPositive)
    {
        value *= -1;
    }

    return value;
}

std::string BigInt::getString() const
{
    std::stringstream stream;

    if (!mIsPositive)
    {
        stream << "-";
    }

    for (int i = mValue.size() - 1; i >= 0 ; i--)
    {
        stream << static_cast<int>(mValue[i]);
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

    int positiveRoll = distribution(generator);
    bool isPositive = true;
    if (positiveRoll < 5)
    {
        isPositive = false;
    }

    return BigInt(isPositive, value);
}

//=============================================================================**
// Addition Operator
//=============================================================================**
BigInt BigInt::operator+(const BigInt& other) const
{
    // Opposite signs result in subtraction
    if (mIsPositive != other.mIsPositive)
    {
        BigInt flipSignOther(other);
        flipSignOther.mIsPositive = !flipSignOther.mIsPositive;

        return (*this - flipSignOther);
    }

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

    return BigInt(mIsPositive, value);
}

//=============================================================================**
// Subtraction Operator
//=============================================================================**
BigInt BigInt::operator-(const BigInt& other) const
{
    // Opposite signs results in addition.
    if (mIsPositive != other.mIsPositive)
    {
        BigInt flipSignOther(other);
        flipSignOther.mIsPositive = !flipSignOther.mIsPositive;

        return (*this + flipSignOther);
    }

    // The greater value in magnitude should be first
    if (*this < other)
    {
        BigInt result = other - *this;
        result.mIsPositive = !result.mIsPositive;
        return result;
    }

    // Subtraction
    uint8_t maxSize = std::max(mValue.size(), other.mValue.size());
    std::vector<uint8_t> value(maxSize);

    bool changeSign = false;
    uint8_t takeAway = 0;
    for (unsigned int i = 0; i < maxSize; ++i)
    {
        uint8_t a = i < mValue.size() ? mValue[i] : 0;
        uint8_t b = i < other.mValue.size() ? other.mValue[i] : 0;

        int8_t temp = a - b - takeAway;

        if (temp >= 0)
        {
            value[i] = static_cast<uint8_t>(temp);
            takeAway = 0;
        }
        else if (i < mValue.size() - 1)
        {
            value[i] = static_cast<uint8_t>(temp + 10);
            takeAway = 1;
        }
        else
        {
            value[i] = -temp;
            changeSign = true;
        }
    }
    return BigInt(changeSign ? !mIsPositive : mIsPositive, value);
}

//=============================================================================**
// Multiplication Operator
//=============================================================================**
BigInt BigInt::operator*(const BigInt& other) const
{
    BigInt total(0);
    BigInt add(true, mValue);

    for (BigInt i(0); i < other; i = i + BigInt(1))
    {
        total = total + add;
    }

    if (mIsPositive != other.mIsPositive)
    {
        total.mIsPositive = false;
    }

    return total;
}

//=============================================================================**
// Less Than Operator (IGNORES POSITIVE - ONLY MAGNITUDE)
//=============================================================================**
bool BigInt::operator<(const BigInt& other) const
{
    bool isLessThan = false;

    if (mValue.size() == other.mValue.size())
    {
        for (int i = 0; i < mValue.size() && !isLessThan; ++i)
        {
            isLessThan = mValue[i] < other.mValue[i];
        }
    }
    else
    {
        return mValue.size() < other.mValue.size();
    }

    return isLessThan;
}

//=============================================================================**
// Output Operator
//=============================================================================**
std::ostream& operator<<(std::ostream& out, const BigInt& bigInt)
{
    out << bigInt.getString();
    return out;
}
