//
// Created by Adrian Hwang on 2024-09-15.
//

#ifndef FLIPSHIFT_H
#define FLIPSHIFT_H
#include <iostream>
#include <cmath>
int nearestPowerOfTwo(int n) {
    if (n == 0) return 1;
    if ((n & (n - 1)) == 0) return n;  // Already a power of 2
    //or by n%2==0

    //n is not the power of 2
    // integer << 1 means integer times 2
    // 1<<1 = 2^1
    int smaller_powerOfTwo=1<<(int)(std::log2(n));
    int larger_powerOfTwo=1<<(int)(std::log2(n)+1);
    return (n-smaller_powerOfTwo<larger_powerOfTwo-n)?smaller_powerOfTwo:larger_powerOfTwo;
    //std::log2(n) returns a double type, double y such that 2^y=n
    //(int)(std::log2(n) + 1); e.g. 2^3.5 -> 2^4; 2^3.2 - >2^4
}

int countBitFlips(int c, int c_apo) {
    int xorResult = c ^ c_apo;
    int count = 0;
    while (xorResult > 0) {
        count += xorResult & 1;  // Count the number of LSB
        xorResult >>= 1;
    }
    return count;
}

int countShiftOperations(int a_apo, int b_apo) {
    int shifts = 0;
    while (a_apo < b_apo) {
        a_apo <<= 1;  // Shift left
        shifts++;
    }
    return shifts;
}

int* flipShift(int a, int b) {
    int* result=new int[3];

    int a_apo = nearestPowerOfTwo(a);
    int b_apo = nearestPowerOfTwo(b);

    result[0] = a_apo;  // Nearest power of 2 for a
    result[1] = b_apo;  // Nearest power of 2 for b

    result[0] = countBitFlips(a, a_apo);  // Number of bit flips for a to a_apo
    result[1] = countBitFlips(b, b_apo); //b to b_apo
    result[2] = countShiftOperations(a_apo, b_apo);  // Number of shift lefts

    std::cout << "a to a' flips " << result[0]<<" bits, b to b' flips " << result[1]<<" bits, a' shifts to b' by "<<result[2]<<" bits."<<std::endl;  // Number of bit flips
    return result; //return a pointer
}
#endif //FLIPSHIFT_H
