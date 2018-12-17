#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


Matrice *aleaMatrixBinaire(int m, int n) {

    printf("Creating a matrix of size %dx%d\n", m,n);
    Matrice *matrice = malloc(sizeof(Matrice));
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


void showMatrix(Matrice * M, unsigned int start, unsigned int end) {
    unsigned int k = 1;
    for (int i = start; i < end; i++) {
        printf("k = %d : %llu;", k, M->value[i]);
        if((k)%M->n == 0) {
            printf("\n");
        }
        k++;
    }
}