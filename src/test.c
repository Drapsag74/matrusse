//
// Created by typs on 09/04/19.
//
#include <stdlib.h>
#include <stdio.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "fourRussianAlgorithm.h"
#include "fourRussianAlgorithmV2.h"
#include "matrix.h"


int main(int argc, char * argv[]) {
    matrix_t * A=aleaMatrixBinaire(16384,16384);
    //matrix_t * B=identiterMatrix(64);
    //showMatrix(A);
    //printf("\n");
    //printf("\n");

    clock_t t = clock();
    matrix_t * C=matrusseV2(A,A,8);
    //showMatrixBits(A);
    clock_t t2 = clock();
    //showMatrix(C);
    printf("temps d'exec : %ld \n", (t2-t)/CLOCKS_PER_SEC);

    //showMatrixBits(C);
    freeMatrix(C);

    //showMatrix(B);
    //showMatrix(C);
    freeMatrix(A);
    //freeMatrix(B);

    return 0;
}