//
// Created by Utilisateur on 16/04/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "4RusIntrin.h"
#include <emmintrin.h>
#include <immintrin.h>
#include <time.h>

int main(int argc, char * argv[]) {
    matrix_t * A=aleaMatrixBinaire(16384,16384);
    //matrix_t * B=identiterMatrix(64);
    //showMatrix(A);
    //printf("\n");
    //printf("\n");
    clock_t t = clock();
    matrix_t * C=matrusseIntrin(A,A,8);
    clock_t t2 = clock();
    printf("exec time = %d\n",(t2-t)/CLOCKS_PER_SEC);
    //showMatrix(B);
    //showMatrix(C);
    freeMatrix(A);
    //freeMatrix(B);
    freeMatrix(C);
    return 0;
}