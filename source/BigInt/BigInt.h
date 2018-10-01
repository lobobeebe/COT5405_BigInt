#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>
#include <random>

class BigInt
{
    public:
        BigInt();

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

        static BigInt getRandom(std::default_random_engine& generator, unsigned int numDigits);

    private:
        void trim();

        static std::default_random_engine sGenerator;

        std::vector<uint8_t> mValue;

        bool mIsPositive;
};

std::ostream& operator<<(std::ostream& out, const BigInt& bigInt);
