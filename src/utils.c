#include "utils.h"


matrix_t * aleaMatrixBinaire(int m, int n) {

    //TODO use inttype PRId64
    printf("Creating a matrix of size %dx%d\n", m,n);
    matrix_t *matrice = malloc(sizeof(matrix_t));
    matrice->nbColonneInt=n / (sizeof(long long int) * 8);
    int nbInt=0;
    matrice->m = m;
    matrice->n = n ;

    if (matrice->nbColonneInt * sizeof(long long int) * 8 == n) {
        matrice->value = malloc(matrice->nbColonneInt * sizeof(long long int) * m);
        for (int i = 0; i < m * matrice->nbColonneInt; i++) {
            matrice->value[i] = random_64();
        }
    } else {
        matrice->nbColonneInt++;
        int64_t mask=0;
        int64_t tmp;
        for(int i=0;i<matrice->n%64;i++){
            tmp=1;
            tmp=tmp<<63-i;
            mask+=tmp;
        }
        matrice->value = malloc((matrice->nbColonneInt) * sizeof(long long int) * m);

        for (int i = 0; i < m * matrice->nbColonneInt; i++) {
            matrice->value[i] = random_64();
            if((i+1)%(matrice->nbColonneInt)==0){
                matrice->value[i] =matrice->value[i] & mask;
            }
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
        printf("%16"PRIx64" ",M->value[i]);
        //printf(" %d et %d",(i+1)%(M->n/64+1),M->n/64);
        if((i+1)%(M->nbColonneInt)==0){
            printf("]\n");
            if(i < M->m*M->nbColonneInt-1){
                printf("[");
            }
        }/*
        if ((k) % M->n == 0) {
            printf("\n");
        }*/
        //k++;
    }
}

int64_t readInt64_t(matrix_t * matrice,long int indexRow,long int indexColumns){
    return matrice->value[indexRow*matrice->nbColonneInt+indexColumns];
}

int64_t random_64() {
    int64_t random=rand();
    random=random<<32;
    return  random+rand();
}

/*int64_t readInt64_t(matrix_t * A, int indexRow, int indexColumns) {
    return A->value[A->n*indexRow+indexColumns];
}*/
