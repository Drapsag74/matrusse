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
#include "utils.h"

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long long) - __builtin_clzll((X)) - 1))

matrix_t * matrusseV1(matrix_t * A, matrix_t * B, int k);



#endif //MATRUSSE_FOURRUSSIANALGORITHM_H