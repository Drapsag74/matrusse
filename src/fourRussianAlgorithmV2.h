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
void matrusseV2(matrix_t * A, matrix_t * B, matrix_t * C, int k);

/**
 * ONLY FOR TESTING BEST VALUE FOR BLOCKSIZE
 * @param A Matrix A
 * @param B Matrix B
 * @param k k
 * @param blocksize
 * @return result of the product A*B
 */
void matrusseV2TestBloc(matrix_t * A, matrix_t * B, matrix_t * C, int k, uint32_t blocksize);

/**
 * Version with fillTable2
 * @param A Matrix A
 * @param B Matrix B
 * @param k k
 * @param blocksize
 * @return result of the product A*B
 */
void matrusseV2_2(matrix_t * A, matrix_t * B, matrix_t * C, int k);

void matrusseV2_1TestBloc(matrix_t * A, matrix_t * B, matrix_t * C, int k, uint32_t blocksize);

void matrusseV2SpeedOfLight(matrix_t * A, matrix_t * B, matrix_t * C, int k, uint32_t blocksize);

#endif //MATRUSSE_FOURRUSSIANALGORITHMV2_H
