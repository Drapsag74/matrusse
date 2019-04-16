//
// Created by typs on 12/04/19.
//

#include "fourRussianAlgorithmV2.h"



//note : k_ sert à stocker la valeur initiale de k
void fillTable(uint64_t * T, matrix_t * B, int k, int k_){
    uint32_t n = B->nbColonneInt;
    if(k==0) {
        for(int i=0; i < n; i++) {
            T[i] = 0;
        }
    } else {
        fillTable(T,B,k-1,k_);
        int temp=1<<k-1;
        for(int i=0;i<temp;i++) {
            for(int j=0;j < n;j++) {
                T[(temp + i)*n + j] = T[i*n+j]^readInt64_t(B, k_-k,j);
            }
        }
    }
}

void showT(uint64_t * T, uint64_t size, uint64_t k) {
    printf("Showing table T : \n");
    for (uint64_t i = 0; i < (1 << k); i++) {
        printf("[");
        for (uint64_t j = 0; j < size; j++) {
            printf("%16"PRIx64"\t", T[i * size + j]);
        }
        printf("]");
        printf("\n");
    }
}


    matrix_t * matrusse(matrix_t * A, matrix_t * B, int k) {
    uint32_t m = A->m;
    uint32_t blocksize = m/TAILLE_BLOC;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;
    matrix_t * C = nullMatrix(m, nbits);
    for (int start = 0; start < m/blocksize; ++start) {
        for (int i = 0; i < l/k; ++i) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<k);
            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            fillTable(T, Bbloc, k, k);
            for (int s = 0; s < blocksize; ++s) {
                uint64_t j = start*blocksize + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(T);
            free(Bbloc);
        }
    }

    uint64_t kReste = k*A->n;
    return C;
}