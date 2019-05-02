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
#include "4RusThread.h"

int main(int argc, char * argv[]) {
    matrix_t * A=aleaMatrixBinaire(10000,10000);
    matrix_t * C=aleaMatrixBinaire(10000,10000);
    //matrix_t * B = identiterMatrix(4096);
    //matrix_t * B=identiterMatrix(64);
    //showMatrix(A);
    //printf("\n");
    //printf("\n");

    clock_t t = clock();
    matrix_t * B= matrusseV2(A,C,8);
    //showMatrix(A);
    clock_t t2 = clock();
    printf("time : %li ", (t2-t)/CLOCKS_PER_SEC);
    //showMatrix(C);
    /*int64_t * T=createTable(A,8);
    fillTable2(T,getBloc(A,0,7),8,8);
    matrix_t * C=matrixVide(1<<8,512);
    C->value=T;
    showMatrix(A);*/
   // showMatrix(C);
    //printf("temps d'exec : %ld \n", (t2-t)/CLOCKS_PER_SEC);

    //showMatrixBits(C);
    free(B->value);
    free(B);
    free(C->value);
    free(C);
    //showMatrix(B);
    //showMatrix(C);
    free(A->value);
    free(A);
    //free(B->value);
    //free(B);
    //freeMatrix(B);

    //free(T);

    return 0;
}
