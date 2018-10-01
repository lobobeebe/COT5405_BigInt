#include "BigInt.h"
#include <sstream>
#include <chrono>

BigInt::BigInt() :
    mIsPositive(true)
{
    mValue.push_back(0);
}

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

BigInt BigInt::getRandom(std::default_random_engine& generator, unsigned int numDigits)
{
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
    // Given two integers A and B, represented as vectors [an-1, an-2, ..., a0] and [bm-1, bm-2, ..., b0], respectively, where n cardinality of A and m is the cardinality of B.
    // Let the result, C, be the vector of cardinality (n + m) where all values in C are initially 0.

    // A is the integer defined by this object
    // B is the integer defined by object "other"

    // Allocate vector C with cardinality (n + m)
    std::vector<uint8_t> results(mValue.size() + other.mValue.size(), 0);

    // Allocate a value for the carry over between digits. Carry over is initially 0.
    uint8_t carryOver = 0;

    // For each digit index in A, i:
    for (int i = 0; i < mValue.size(); ++i)
    {
        // For each digit index in B, j:
        for (int j = 0; j < other.mValue.size(); ++j)
        {
            // Calculate A[i] * B[j] once for efficiency
            uint8_t mult = mValue[i] * other.mValue[j];

            // Add (k + A[i] * B[j]) % 10 to C[i + j], where k is the carryover
            results[j + i] += carryOver + mult % 10;

            // let k be (A[i] * B[j]) / 10
            carryOver = mult / 10;
        }

        // Add k to C[i + m]
        results[i + other.mValue.size()] += carryOver;

        // Assign 0 to k
        carryOver = 0;
    }

    // Create the BigInt from the vector
    // Only negative if the signs are different
    BigInt total(mIsPositive == other.mIsPositive, results);

    return total;
}

//=============================================================================**
// Less Than Operator (IGNORES NEGATIVE - ONLY MAGNITUDE)
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
