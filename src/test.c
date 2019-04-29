//
// Created by typs on 09/04/19.
//
#include <stdlib.h>
#include <stdio.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <time.h>
#include <unistd.h>

#include "fourRussianAlgorithm.h"
#include "fourRussianAlgorithmV2.h"
#include "matrix.h"
#include "4RusThread.h"


int main(int argc, char * argv[]) {
    matrix_t * A=aleaMatrixBinaire(6000,6000);
    //matrix_t * B=identiterMatrix(64);
    //showMatrix(A);
    //printf("\n");
    //printf("\n");

    clock_t t = clock();
    matrix_t * C=matrusseThreadV2(A,A,8,4);
    //showMatrixBits(A);
    clock_t t2 = clock();
    /*int64_t * T=createTable(A,8);
    fillTable2(T,getBloc(A,0,7),8,8);
    matrix_t * C=matrixVide(1<<8,512);
    C->value=T;
    showMatrix(A);*/
    //showMatrix(C);
    //printf("temps d'exec : %ld \n", (t2-t)/CLOCKS_PER_SEC);

    //showMatrixBits(C);
    freeMatrix(C);

    //showMatrix(B);
    //showMatrix(C);
    freeMatrix(A);
    //freeMatrix(B);

    //free(T);

    return 0;
}