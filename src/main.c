#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define sizeRow 128

int main(int argc, char *argv[]) {

    printf("Running test \n");
    Matrice * A = aleaMatrixBinaire(sizeRow, sizeRow);
    printf("m=%d, n=%d\n", A->m, A->n);

    showMatrix(A, 0, (int)A->m * A->n);

    return 0;

}

void addRowFromTable(Matrice * C, int indexRowC, Matrice * T, int indexRowT) {
    long long int * rowC = C->value + indexRowC*C->n;
    long long int * rowT = T->value + indexRowT*T->n;
    for(int j = 0; j < C->n; j++){
        rowC[j] ^= rowT[j];
    }
}

long long int readBits(Matrice * A, int indexRow, int indexColumns, int k) {
    long long int id = 0;
    char * K = A->value + A->n*indexRow+indexColumns;
    for (int i = 0; i < k/8; i++) {
        id += K[i] << 8;
    }
    return id;
}

long long int readBits(Matrice * A, int indexRow, int indexColumns, int k) {
    long long int id = 0;
    char * K = A->value + A->n*indexRow+indexColumns;
    for (int i = 0; i < k/8; i++) {
        id += K[i] << 8;
    }
    return id;
}

long long int * MakeTable(Matrice * A, Matrice * B, int k){
    long long int * T = malloc((A->n*sizeof(*A->value))<<k);
    return T;
}

Matrice MethodeOfTheFourRussians(Matrice * A, Matrice * B, int k){

    for (int i = 0; i < A->m; i++) {
        id += K[i] << 8;
    }

}