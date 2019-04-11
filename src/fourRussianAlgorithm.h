//
// Created by typs on 09/04/19.
//
#ifndef MATRUSSE_FOURRUSSIANALGORITHM_H
#define MATRUSSE_FOURRUSSIANALGORITHM_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "matrix.h"

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long long) - __builtin_clzll((X)) - 1))

void addRowFromTable(matrix_t * C, int indexRowC, matrix_t * T, int indexRowT);
/**
 * Create the table of linear combination
 * @param B
 * @param k
 * @return the table of linear combination
 */
int64_t * createTable(matrix_t * B, int k);
void fillTable2(int64_t * T, matrix_t * B, int k, int k_);
void fillTable(int64_t * T, matrix_t * B, int k);
void showT(int64_t * T, int64_t size, int64_t k);
/**
 * 4 russian method
 * @param A
 * @param B
 * @param k
 * @return C the matrix resulting of A*B
 */
matrix_t * matrusse(matrix_t * A, matrix_t * B, int k);


#endif //MATRUSSE_FOURRUSSIANALGORITHM_H
