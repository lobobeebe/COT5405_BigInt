# COT5405_BigInt
Write a program to add/subtract/multiply/divide two n-digit signed integers (where n ranges from 1 to 1000). 

*Multiplication Pseudo-Code*

Given two integers A and B, represented as vectors [an-1, an-2, ..., a0] and [bm-1, bm-2, ..., b0], respectively, where n cardinality of A and m is the cardinality of B.
Let the result, C, be the vector of cardinality (n + m) where all values in C are initially 0. 

For each digit index in A, i:
    For each digit index in B, j:
        Add (k + A[i] * B[j]) % 10 to C[i + j], where k is the carryover and initially 0
        let k be (A[i] * B[j]) / 10 
    Add k to C[i + m]
    Assign 0 to k
