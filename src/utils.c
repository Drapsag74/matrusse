#include "utils.h"


matrix_t * aleaMatrixBinaire(int m, int n) {

    //TODO use inttype PRId64
    printf("Creating a matrix of size %dx%d\n", m,n);
    matrix_t *matrice = malloc(sizeof(matrix_t));
    int nbColonne = n / (sizeof(long long int) * 8);

    if (nbColonne * sizeof(long long int) * 8 == n) {
        matrice->value = malloc(nbColonne * sizeof(long long int) * m);
        matrice->m = m;
        matrice->n = nbColonne;
    } else {
        matrice->value = malloc((nbColonne + 1) * sizeof(long long int) * m);
        matrice->m = m;
        matrice->n = nbColonne + 1;
    }
    for (int i = 0; i < matrice->m * matrice->n; i++) {
        matrice->value[i] = rand();
    }
    return matrice;

}


void showMatrix(matrix_t * M, unsigned int start, unsigned int end) {
    unsigned int k = 1;
    for (int i = start; i < end; i++) {
        //TODO show matrix beautifully, USE inttypes macro PRId64
        //printf("k = %d : %llu;", k, M->value[i]);
        if ((k) % M->n == 0) {
            printf("\n");
        }
        k++;
    }
}

int64_t readInt64_t(matrix_t * A, int indexRow, int indexColumns) {
    return A->value[A->n*indexRow+indexColumns];
}
