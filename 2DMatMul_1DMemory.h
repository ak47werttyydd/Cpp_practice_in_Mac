//
// Created by Adrian Hwang on 2024-09-23.
//

#ifndef INC_2DMATMUL_1DMEMORY_H
#define INC_2DMATMUL_1DMEMORY_H
#include <iostream>
#include <vector>

using namespace std;

// Function to perform matrix multiplication with 1D arrays
vector<int> matrixMultiply1D(const vector<int>& A, const vector<int>& B, int n, int m, int k) {
    // Result matrix C (n x k), initialized to 0
    //A n x m
    //B m x k
    vector<int> C(n * k, 0);

    // Perform matrix multiplication
    for (int i = 0; i < A.size(); i+=m) {           // Iterate over rows of A
        for (int j = 0; j < k; ++j) {       // Iterate over columns of B
            for (int p = 0; p < m; ++p) {   // Iterate over columns of A and rows of B
                C[i + j] += A[i + p] * B[p*k + j];
            }
        }
    }

    return C;
}
#endif //INC_2DMATMUL_1DMEMORY_H
