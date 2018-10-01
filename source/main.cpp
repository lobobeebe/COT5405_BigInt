#include "BigInt/BigInt.h"
#include <fstream>
#include <chrono>
#include <string>
#include <stdlib.h>

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Format: <Executable Name>.exe <Num Digits> <Num Iterations>" << std::endl;
        return 1;
    }

    int numDigits = std::atoi(argv[1]);
    int numIterations = std::atoi(argv[2]);

    // Create file stream to track results
    // FORMAT: OPERAND0, OPERAND1, RESULT, DURATION (us)
    std::ofstream perfStream;
    perfStream.open(std::to_string(numDigits) + "_" + std::to_string(numIterations) + "_mult_perf.csv");

    // Random number generator
    std::default_random_engine generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

    // For each iteration
    for (int i = 0; i < numIterations; ++i)
    {
        // Get random values of size numDigits (this time not calculated in performance)
        BigInt val0 = BigInt::getRandom(generator, numDigits);
        BigInt val1 = BigInt::getRandom(generator, numDigits);

        // Start Time
        auto start = std::chrono::high_resolution_clock::now();

        // Multiplication
        BigInt result = val0 * val1;

        // Stop Time
        auto stop = std::chrono::high_resolution_clock::now();

        // Calculate duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        // Print out result/performance
        perfStream << val0.getString() << "," << val1.getString() << ","
            << result.getString() <<"," << duration.count() << std::endl;
    }

    perfStream.close();

    return 0;
}
