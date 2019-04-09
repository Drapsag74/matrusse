#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

#include "utils.h"
#include "fourRussianAlgorithm.h"

#define sizeRow 128


int main(int argc, char *argv[]) {
    int k = 20;
    struct matrix_t * m = aleaMatrixBinaire(k,1<<15);
    //showMatrix(m);
    /*
    printf("Running test \n");
    matrix_t * A = aleaMatrixBinaire(sizeRow, sizeRow);
    printf("m=%d, n=%d\n", A->m, A->n);

    showMatrix(A, 0, (int)A->m * A->n);
    readInt64_t(A,3,3);*/

    int64_t * T = createTable(m, k);
    clock_t t;
    clock_t t2;

    //showT(T, m->nbColonneInt, k);
    t = clock();
    fillTable2(T, m, k,k);
    t2 = clock();
    printf("Temps d'exécution de l'algo de Guillhem :%d \n",t2-t);
    /*t = clock();
    fillTable(T, m, k);
    t2 = clock();
    printf("Temps d'exécution de l'algo de Gaspard :%d",t2-t);*/
    //showT(T, m->nbColonneInt, k);

    return 0;

}

