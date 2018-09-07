#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

class BigInt
{
    public:
        BigInt(const BigInt& other);

        BigInt(bool isPositive, const std::vector<uint8_t>& value);

        BigInt(int64_t value);

        std::string getString() const;

        int64_t getIntValue() const;

        BigInt operator+(const BigInt& other) const;
        BigInt operator-(const BigInt& other) const;
        BigInt operator*(const BigInt& other) const;
        //BigInt operator/(const BigInt& other) const;

        bool operator<(const BigInt& other) const;

        static BigInt getRandom(unsigned int numDigits);

    private:
        void trim();

        std::vector<uint8_t> mValue;

        bool mIsPositive;
};

std::ostream& operator<<(std::ostream& out, const BigInt& bigInt);
