//
// Created by typs on 12/04/19.
//

#include "fourRussianAlgorithmV2.h"
#include "utils.h"

void calculResteK(matrix_t * A, matrix_t * B, matrix_t * C, uint32_t kReste, uint32_t  n, uint32_t l, uint32_t blocksize, int start) {
    //alocating table of 2^k * B->nbColonneInt
    uint64_t * T = malloc((n*sizeof(uint64_t))<<kReste);
    matrix_t * Bbloc = getBloc(B, l - kReste, kReste);
    fillTable(T, Bbloc, kReste);
    for (int s = 0; s < blocksize; ++s) {
        uint64_t j = start*blocksize + s;
        int64_t id = extract(A,j, l - kReste, kReste);
        uint64_t * Tline = T+id*n;
        xorMatrixRow(C, j, Tline);
    }
    free(Bbloc);
    Bbloc = NULL;
    free(T);
    T = NULL;
}


matrix_t * matrusseV2(matrix_t * A, matrix_t * B, int k) {

    uint32_t m = A->m;
    uint32_t blocksize = TAILLE_BLOC;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;

    matrix_t * C = nullMatrix(m, nbits);

    for (int start = 0; start < m/blocksize; ++start) {
        //progressBar(start,m/blocksize-1);

        for (int i = 0; i < l/k; ++i) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<k);
            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            fillTable(T, Bbloc, k);
            for (int s = 0; s < blocksize; ++s) {
                uint64_t j = start*blocksize + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;
            free(T);
            T = NULL;
        }

        uint32_t kReste = l%k;
        if (kReste != 0) {
            calculResteK(A, B, C, kReste, n, l, blocksize, start);
        }
    }
    uint32_t blocksizeReste = m%blocksize;
    if(blocksizeReste != 0) {

        int start = m - blocksizeReste;

        for (int i = 0; i < l/k; ++i) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<k);
            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            fillTable(T, Bbloc, k);
            for (int s = 0; s < blocksizeReste; ++s) { //scanning throught the last block
                uint64_t j = start + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;
            free(T);
            T = NULL;
        }

        uint32_t kReste = l%k;
        if (kReste != 0) {
            calculResteK(A, B, C, kReste, n, l, blocksize, start);
        }
    }


    return C;
}

matrix_t * matrusseV2TestBloc(matrix_t * A, matrix_t * B, int k, uint32_t blocksize) {

    uint32_t m = A->m;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;

    matrix_t * C = nullMatrix(m, nbits);

    for (int start = 0; start < m/blocksize; ++start) {
        //progressBar(start,m/blocksize-1);

        for (int i = 0; i < l/k; ++i) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<k);
            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            fillTable(T, Bbloc, k);
            for (int s = 0; s < blocksize; ++s) {
                uint64_t j = start*blocksize + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;
            free(T);
            T = NULL;
        }

        uint32_t kReste = l%k;
        if (kReste != 0) {
            calculResteK(A, B, C, kReste, n, l, blocksize, start);
        }
    }
    uint32_t blocksizeReste = m%blocksize;
    if(blocksizeReste != 0) {

        int start = m - blocksizeReste;

        for (int i = 0; i < l/k; ++i) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<k);
            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            fillTable(T, Bbloc, k);
            for (int s = 0; s < blocksizeReste; ++s) { //scanning throught the last block
                uint64_t j = start + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;
            free(T);
            T = NULL;
        }

        uint32_t kReste = l%k;
        if (kReste != 0) {
            calculResteK(A, B, C, kReste, n, l, blocksize, start);
        }
    }

    return C;
}

matrix_t * matrusseV2_2(matrix_t * A, matrix_t * B, int k) {

    uint32_t m = A->m;
    uint32_t blocksize = TAILLE_BLOC;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;

    matrix_t * C = nullMatrix(m, nbits);

    for (int start = 0; start < m/blocksize; ++start) {
        //progressBar(start,m/blocksize-1);

        for (int i = 0; i < l/k; ++i) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<k);
            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            fillTable2(T, Bbloc, k, k);
            for (int s = 0; s < blocksize; ++s) {
                uint64_t j = start*blocksize + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            freeBloc(Bbloc);
            free(T);
        }

        int kReste = l%k;
        if (kReste != 0) {
            calculResteK(A, B, C, kReste, n, l, blocksize, start);
        }
    }

    return C;
}