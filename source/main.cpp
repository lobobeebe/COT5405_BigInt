#include "BigInt/BigInt.h"
#include <iostream>

int main()
{
    std::vector<uint8_t> value0;
    value0.push_back(5);
    value0.push_back(4);
    value0.push_back(3);
    value0.push_back(2);
    value0.push_back(1);
    value0.push_back(0);
    BigInt val0 = BigInt(false, value0);

    std::vector<uint8_t> value1;
    value1.push_back(5);
    value1.push_back(6);
    value1.push_back(7);
    value1.push_back(8);
    value1.push_back(9);
    value0.push_back(0);
    BigInt val1 = BigInt(true, value1);

    std::cout << val0 << " + " << val1 << " = " << (val0 + val1) << std::endl;
    std::cout << val0 << " - " << val1 << " = " << (val0 - val1) << std::endl;
    //std::cout << val0 << " - " << val1 << " = " << (val0 + val1) << std::endl;
    //std::cout << val0 << " + " << val1 << " = " << (val0 + val1) << std::endl;

    return 0;
}
