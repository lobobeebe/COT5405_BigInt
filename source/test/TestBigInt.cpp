#include "BigInt.h"
#include <iostream>

int gNumTestsFailed = 0;

bool assert(bool assertion, int lineNum)
{
    if (!assertion)
    {
        gNumTestsFailed++;
    }

    return assertion;
}

void assertEqual(int64_t expected, int64_t actual, int lineNum)
{
    if (!assert(actual == expected, lineNum))
    {
        std::cout << __FILE__ << ":" << lineNum << ": Test Failed! Expected: " << expected << ", Actual: " << actual << std::endl;
    }
}

void testAddition()
{
    std::vector<uint8_t> value0;
    value0.push_back(5);
    value0.push_back(4);
    value0.push_back(3);
    value0.push_back(2);
    value0.push_back(1);
    value0.push_back(0);
    BigInt bigInt0 = BigInt(true, value0); // 12345

    std::vector<uint8_t> value1;
    value1.push_back(0);
    value1.push_back(1);
    value1.push_back(2);
    value1.push_back(3);
    value1.push_back(4);
    value1.push_back(5);
    BigInt bigInt1 = BigInt(true, value1); // 543210

    BigInt result = bigInt0 + bigInt1;
    assertEqual(555555, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(false, value0); // -12345
    bigInt1 = BigInt(true, value1); // 543210

    result = bigInt0 + bigInt1;
    assertEqual(530865, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(false, value0); // -12345
    bigInt1 = BigInt(false, value1); // -543210

    result = bigInt0 + bigInt1;
    assertEqual(-555555, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(true, value0); // 123345
    bigInt1 = BigInt(false, value1); // -543210

    result = bigInt0 + bigInt1;
    assertEqual(-530865, result.getIntValue(), __LINE__);
}

void testSubtraction()
{
    BigInt bigInt0 = BigInt(12345);
    BigInt bigInt1 = BigInt(543210);

    BigInt result = bigInt0 - bigInt1;
    assertEqual(-530865, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(-12345);
    bigInt1 = BigInt(543210);

    result = bigInt0 - bigInt1;
    assertEqual(-555555, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(-12345);
    bigInt1 = BigInt(-543210);

    result = bigInt0 - bigInt1;
    assertEqual(530865, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(12345);
    bigInt1 = BigInt(-543210);

    result = bigInt0 - bigInt1;
    assertEqual(555555, result.getIntValue(), __LINE__);
}

void testMultiplication()
{
    BigInt bigInt0 = BigInt(123450);
    BigInt bigInt1 = BigInt(54321);

    BigInt result = bigInt0 * bigInt1;
    assertEqual(6705927450, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(-12345);
    bigInt1 = BigInt(543210);

    result = bigInt0 * bigInt1;
    assertEqual(-6705927450, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(-12345);
    bigInt1 = BigInt(-543210);

    result = bigInt0 * bigInt1;
    assertEqual(6705927450, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(12345);
    bigInt1 = BigInt(-543210);

    result = bigInt0 * bigInt1;
    assertEqual(-6705927450, result.getIntValue(), __LINE__);

    bigInt0 = BigInt(99);
    bigInt1 = BigInt(99999);

    result = bigInt0 * bigInt1;
    assertEqual(9899901, result.getIntValue(), __LINE__);
}

void testGetIntValue()
{
    std::vector<uint8_t> value0;
    value0.push_back(5);
    value0.push_back(4);
    value0.push_back(3);
    value0.push_back(2);
    value0.push_back(1);
    value0.push_back(0);
    BigInt val0 = BigInt(false, value0);
    assertEqual(-12345, val0.getIntValue(), __LINE__);

    value0.push_back(0);
    value0.push_back(1);
    value0.push_back(2);
    val0 = BigInt(true, value0);
    assertEqual(210012345, val0.getIntValue(), __LINE__);
}

int main()
{
    testGetIntValue();
    testAddition();
    testSubtraction();
    testMultiplication();

    std::cout << "Num Tests Failed = " << gNumTestsFailed << std::endl;
}
