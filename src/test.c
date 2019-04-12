//
// Created by typs on 09/04/19.
//
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "fourRussianAlgorithm.h"
#include <emmintrin.h>
#include <immintrin.h>


int main(int argc, char * argv[]) {
    matrix_t * A=aleaMatrixBinaire(64,64);
    matrix_t * B=identiterMatrix(64);
    showMatrix(A);
    printf("\n");
    showMatrix(B);
    printf("\n");
    matrix_t * C=matrusse(A,B,8);
    showMatrix(C);
    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C);
    return 0;
}