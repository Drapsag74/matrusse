#include "utils.h"


matrix_t * aleaMatrixBinaire(int m, int n) {

    //TODO use inttype PRId64
    printf("Creating a matrix of size %dx%d\n", m,n);
    matrix_t *matrice = malloc(sizeof(matrix_t));
    matrice->nbColonneInt=n / (sizeof(long long int) * 8);
    int nbInt=0;

    if (matrice->nbColonneInt * sizeof(long long int) * 8 == n) {
        matrice->value = malloc(matrice->nbColonneInt * sizeof(long long int) * m);
        matrice->m = m;
        matrice->n = n;
        for (int i = 0; i < m * matrice->nbColonneInt; i++) {
            matrice->value[i] = rand();
            nbInt++;
        }
    } else {
        matrice->value = malloc((matrice->nbColonneInt + 1) * sizeof(long long int) * m);
        matrice->m = m;
        matrice->n = n + 1;
        for (int i = 0; i < m * matrice->nbColonneInt+1; i++) {
            matrice->value[i] = rand();
            nbInt++;
        }
    }

    return matrice;

}


void showMatrix(matrix_t * M/*, unsigned int start, unsigned int end*/) {
    //unsigned int k = 1;
    printf("[");
    for (int i = 0; i < M->m*M->nbColonneInt; i++) {
        //TODO show matrix beautifully, USE inttypes macro PRId64
        //printf("k = %d : %llu;", k, M->value[i]);
        printf("%8"PRIx64" ",M->value[i]);
        //printf(" %d et %d",(i+1)%(M->n/64+1),M->n/64);
        if((i+1)%(M->nbColonneInt)==0){
            printf("]\n[");
        }/*
        if ((k) % M->n == 0) {
            printf("\n");
        }*/
        //k++;
    }
    printf("]");
}

int64_t readInt64_t(matrix_t * A, int indexRow, int indexColumns) {
    return A->value[A->n*indexRow+indexColumns];
}
