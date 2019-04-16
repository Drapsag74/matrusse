//
// Created by typs on 16/04/19.
//

#ifndef MATRUSSE_UTILS_H
#define MATRUSSE_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>

#include "matrix.h"

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long long) - __builtin_clzll((X)) - 1))

void fillTable(int64_t * T, matrix_t * B, int k);
void fillTable2(uint64_t * T, matrix_t * B, int k, int k_);
void showT(uint64_t * T, uint64_t size, uint64_t k);
int64_t * createTable(matrix_t * B, int k);
void progressBar(int k, int n);


#endif //MATRUSSE_UTILS_H
