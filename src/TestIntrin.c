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
    matrix_t * A=aleaMatrixBinaire(32000,32000);
    //matrix_t * B=identiterMatrix(64);
    //showMatrix(A);
    //printf("\n");
    //printf("\n");
    clock_t t = clock();
    matrix_t * C=matrusseIntrin(A,A,11);
    clock_t t2 = clock();
    //matrix_t * C=createTableIntrin(A,8);
    //fillTableIntrin(C,getBloc(A,0,7),8,8);
    /*__m256i test=_mm256_loadu_si256(&A->value[4]);
    printf("%16"PRIx64" %16"PRIx64" %16"PRIx64" %16"PRIx64"",test[0],test[1],test[2],test[3]);
    matrix_t * C=nullMatrix(512,512);
    _mm256_storeu_si256(&C->value[4],test);*/
    //showMatrix(C);
    printf("exec time = %d\n",(t2-t)/CLOCKS_PER_SEC);
    //showMatrix(B);
    //showMatrix(C);
    freeMatrix(A);
    //freeMatrix(B);
    freeMatrix(C);
    return 0;
}