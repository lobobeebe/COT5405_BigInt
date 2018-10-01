# COT5405_BigInt
Write a program to add/subtract/multiply/divide two n-digit signed integers (where n ranges from 1 to 1000). 

# Build
Linux:
Run ./buildLinux.sh

MinGW:
Run ./buildMinGW.sh


# Procedure
Our results were captured running on Ubuntu 17.10 64-bit
* Processor: i7-2670qm 2.2GHz x 8
* Memory: 8GB

Tools:
* CMake 3.9.1
* GNU Make 4.1
* massif by Valgrind 3.13.0
* GCC 7.2.0

## Space Complexity
Run the following command:
* "valgrind --tool=massif --max-snapshots=10 --time-unit=B ./Main x 1000", where x is the number of digits to test.
* "ms_print massif.out.XXXXX", where XXXXX is the generated output number.

Using this output, select the greatest value in the "total(B)" column as the total bytes used for the run.

## Time Complexity
Run the following command:
* "./Main x 1000", where x is the number of digits to test

An output CSV file will be generated with the results of each run and the time it took to complete. Average all numbers in the 4th column (time) as the result of this run.
