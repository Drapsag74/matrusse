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
    matrix_t * A=aleaMatrixBinaire(10,64);
    /*printf("%d",extract(B,0,1,8));
    printf("%d",extract(B,1,1,8));
    printf("%d",extract(B,2,1,8));
    printf("%d",extract(B,3,1,8));
    printf("%d",extract(B,4,1,8));
    printf("%d",extract(B,5,1,8));

    printf("\n");*/
    showMatrix(A);
    printf("\n");
    xor(A,1,A,2);
    showMatrix(A);
    freeMatrix(A);
    //freeMatrix(B);
    //freeMatrix(C);
    return 0;
}