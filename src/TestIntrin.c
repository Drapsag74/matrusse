//
// Created by Utilisateur on 16/04/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "4RusIntrin.h"
#include <emmintrin.h>
#include <immintrin.h>

int main(int argc, char * argv[]) {
    matrix_t * A=aleaMatrixBinaire(16000,16000);
    //matrix_t * B=identiterMatrix(64);
    //showMatrix(A);
    //printf("\n");
    //printf("\n");
    matrix_t * C=matrusseIntrin(A,A,11);
    //showMatrix(B);
    //showMatrix(C);
    freeMatrix(A);
    //freeMatrix(B);
    freeMatrix(C);
    return 0;
}