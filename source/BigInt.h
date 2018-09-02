#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

class BigInt
{
    public:
        BigInt(const std::vector<uint8_t>& value);

        std::string getString() const;

        BigInt operator+(const BigInt& other) const;
        //operator-(BigInt other) const;
        //operator*(BigInt other) const;
        //operator/(BigInt other) const;

        static BigInt getRandom(unsigned int numDigits);

    private:
        std::vector<uint8_t> mValue;

        bool mIsNegative;
};

std::ostream operator<<(const std::ostream& out, const BigInt& bigInt)
{
    out << bigInt.getString();
    return out;
}
