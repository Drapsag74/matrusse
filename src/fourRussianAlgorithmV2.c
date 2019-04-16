//
// Created by typs on 12/04/19.
//

#include "fourRussianAlgorithmV2.h"

matrix_t * matrusseV2(matrix_t * A, matrix_t * B, int k) {
    uint32_t m = A->m;
    uint32_t blocksize = TAILLE_BLOC;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;
    matrix_t * C = nullMatrix(m, nbits);
    //TODO threading
    for (int start = 0; start < m/blocksize; ++start) {
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
            free(T);
            free(Bbloc);
        }
    }

    uint64_t kReste = k*A->n;
    return C;
}
