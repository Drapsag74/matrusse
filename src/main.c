#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define sizeRow 128

int main(int argc, char *argv[]) {

    //if (argc < 1) {
    //    printf(" put matrix size");
    //}
    printf("Running test \n");
    Matrice * A = aleaMatrixBinaire(sizeRow, sizeRow);
    printf("m=%d, n=%d\n", A->m, A->n);

    showMatrix(A, 0, (int)A->m * A->n);

    return 0;

}

void addRowFromTable(Matrice * C, int indexRowC, long long int * T, int indexRowT) {
    long long int * rowC = C->matrice + indexRowC*sizeRow;
    long long int * rowT = T + indexRowT*sizeRow;
    for(int j = 0; j < C->n; j++){
        rowC[j] ^= rowT[j];
    }
}

long long int readBits(Matrice * A, int indexRow, int indexColumns, int k) {
    long long int id = 0;
    for (int i = 0; i < k; i++) {
        id ^= A->matrice[A->n*indexRow+indexColumns + i] << (k-i-1);
    }
    return id;
}