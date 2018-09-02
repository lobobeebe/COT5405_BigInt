#include "BigInt.h"
#include <iostream>

int main()
{
    std::vector<uint8_t> value0;
    value0.push_back(5);
    value0.push_back(4);
    value0.push_back(3);
    value0.push_back(2);
    value0.push_back(1);
    BigInt val0 = BigInt(value0);

    std::vector<uint8_t> value1;
    value1.push_back(5);
    value1.push_back(6);
    value1.push_back(7);
    value1.push_back(8);
    value1.push_back(9);
    BigInt val1 = BigInt(value1);

    std::cout << val0.getString() << " + " << val1.getString() << std::endl;

    BigInt result = val0 + val1;

    std::cout << result.getString() << std::endl;

    return 0;
}
