//
// Created by typs on 12/04/19.
//

#ifndef MATRUSSE_FOURRUSSIANALGORITHMV2_H
#define MATRUSSE_FOURRUSSIANALGORITHMV2_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "matrix.h"
#include <string.h>

#define TAILLE_BLOC 16

void fillTable(uint64_t * T, matrix_t * B, int k, int k_);
matrix_t * matrusse(matrix_t * A, matrix_t * B, int k);

#endif //MATRUSSE_FOURRUSSIANALGORITHMV2_H
