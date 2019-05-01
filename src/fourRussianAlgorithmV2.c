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
        uint64_t j = start + s;
        int64_t id = extract(A,j, l - kReste, kReste);
        uint64_t * Tline = T+id*n;
        xorMatrixRow(C, j, Tline);
    }
    free(Bbloc);
    Bbloc = NULL;
    free(T);
    T = NULL;
}

void calculResteK2_1(matrix_t * A, matrix_t * B, matrix_t * C, uint32_t kReste, uint32_t  n, uint32_t l, uint32_t blocksize, int start, uint64_t * T) {

    matrix_t * Bbloc = getBloc(B, l - kReste, kReste);
    fillTable(T, Bbloc, kReste);
    for (int s = 0; s < blocksize; ++s) {
        uint64_t j = start + s;
        int64_t id = extract(A,j, l - kReste, kReste);
        uint64_t * Tline = T+id*n;
        xorMatrixRow(C, j, Tline);
    }
    free(Bbloc);
    Bbloc = NULL;
}

void matrusseV2(matrix_t * A, matrix_t * B, matrix_t * C, int k) {

    uint32_t m = A->m;
    uint32_t blocksize = TAILLE_BLOC;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;

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
            calculResteK(A, B, C, kReste, n, l, blocksize, start*blocksize);
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
            //not multiplying by blocksize because start is already the beginning of the last bloc
            calculResteK(A, B, C, kReste, n, l, blocksizeReste, start);
        }
    }
}

void matrusseV2TestBloc(matrix_t * A, matrix_t * B, matrix_t * C, int k, uint32_t blocksize) {

    uint32_t m = A->m;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;

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
            calculResteK(A, B, C, kReste, n, l, blocksize, start*blocksize);
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
            //not multiplying by blocksize because start is already the beginning of the last bloc
            calculResteK(A, B, C, kReste, n, l, blocksizeReste, start);
        }
    }
}

void matrusseV2_1TestBloc(matrix_t * A, matrix_t * B, matrix_t * C, int k, uint32_t blocksize) {

    uint32_t m = A->m;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;

    //allocating 2^k * B->nbColonneInt * l/k for the table of all subdivision of the matrix
    // add 2^(l%k) * B->nbColonneInt for the reminder
    uint64_t sizeOfATable = ((n*sizeof(uint64_t))<<k);
    uint64_t * Ttable = malloc(sizeOfATable*(l/k) + ((n*sizeof(uint64_t))<<(l%k)));

    for (int start = 0; start < m/blocksize; ++start) {
        //progressBar(start,m/blocksize-1);

        for (int i = 0; i < l/k; ++i) {

            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            uint64_t * T = Ttable + i*sizeOfATable/8;
            if(start == 0) {
                fillTable(T, Bbloc, k);
            }
            for (int s = 0; s < blocksize; ++s) {
                uint64_t j = start*blocksize + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;

        }

        uint32_t kReste = l%k;
        if (kReste != 0) {
            //divided by 8 because of size of uint64_t in bytes
            uint64_t * TReste = Ttable + (l/k)*sizeOfATable/8;
            calculResteK2_1(A, B, C, kReste, n, l, blocksize, start*blocksize, TReste);
        }
    }

    uint32_t blocksizeReste = m%blocksize;
    if(blocksizeReste != 0) {

        int start = m - blocksizeReste;

        for (int i = 0; i < l/k; ++i) {
            //alocating table of 2^k * B->nbColonneInt
            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            uint64_t * T = Ttable + i*sizeOfATable/8;

            for (int s = 0; s < blocksizeReste; ++s) { //scanning throught the last block
                uint64_t j = start + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;

        }
        uint32_t kReste = l%k;
        if (kReste != 0) {
            uint64_t * TReste = Ttable + (l/k)*sizeOfATable/8;
            //not multiplying by blocksize because start is already the beginning of the last bloc
            calculResteK2_1(A, B, C, kReste, n, l, blocksizeReste, start, TReste);
        }
    }
    free(Ttable);
    Ttable = NULL;
}


void matrusseV2_2(matrix_t * A, matrix_t * B, matrix_t * C, int k) {

    uint32_t m = A->m;
    uint32_t blocksize = TAILLE_BLOC;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;

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
            calculResteK(A, B, C, kReste, n, l, blocksize, start*blocksize);
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
            //not multiplying by blocksize because start is already the beginning of the last bloc
            calculResteK(A, B, C, kReste, n, l, blocksizeReste, start);
        }
    }
}

//We'll assume that we are only multiplying matrix with bloc and k multiple of the matrix size
void matrusseV2SpeedOfLight(matrix_t * A, matrix_t * B, matrix_t * C, int k, uint32_t blocksize) {

    uint32_t m = A->m;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;

    //allocating 2^k * B->nbColonneInt * l/k for the table of all subdivision of the matrix
    uint64_t sizeOfATable = ((n * sizeof(uint64_t)) << k);
    uint64_t *Ttable = malloc(sizeOfATable * (l / k));

    for (int start = 0; start < m / blocksize; ++start) {
        //progressBar(start,m/blocksize-1);

        for (int i = 0; i < l/k; ++i) {

            matrix_t *Bbloc = getBloc(B, i * k, i + k);
            uint64_t *T = Ttable + i * sizeOfATable / 8;
            if (start == 0) {
                fillTable(T, Bbloc, k);
            }
            for (int s = 0; s < blocksize; ++s) {
                uint64_t j = start * blocksize + s;
                int64_t id = extract(A, j, k * i, k);
                //create a dummy table matrix to use existing functions
                matrix_t Tline = {.value=T + id*n, .nbColonneInt=n };
                xorMatrixMatrix256i(C,j, &Tline, 0);
            }
            free(Bbloc);
            Bbloc = NULL;

        }
    }

    free(Ttable);
    Ttable = NULL;
}