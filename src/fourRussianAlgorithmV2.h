//
// Created by typs on 12/04/19.
//

#ifndef MATRUSSE_FOURRUSSIANALGORITHMV2_H
#define MATRUSSE_FOURRUSSIANALGORITHMV2_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>

#include "matrix.h"
#include "utils.h"

#define TAILLE_BLOC 1024

#include "utils.h"

/**
 * product of matrix using 4RussianAlgo
 * @param A Matrix A
 * @param B Matrix B
 * @param k k
 * @param blocksize
 * @return result of the product A*B
 */
matrix_t * matrusseV2(matrix_t * A, matrix_t * B, int k);

/**
 * ONLY FOR TESTING BEST VALUE FOR BLOCKSIZE
 * @param A Matrix A
 * @param B Matrix B
 * @param k k
 * @param blocksize
 * @return result of the product A*B
 */
matrix_t * matrusseV2TestBloc(matrix_t * A, matrix_t * B, int k, uint32_t blocksize);

/**
 * Version with fillTable2
 * @param A Matrix A
 * @param B Matrix B
 * @param k k
 * @param blocksize
 * @return result of the product A*B
 */
matrix_t * matrusseV2_2(matrix_t * A, matrix_t * B, int k);

#endif //MATRUSSE_FOURRUSSIANALGORITHMV2_H
