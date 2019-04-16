//
// Created by Utilisateur on 16/04/2019.
//

#ifndef MATRUSSE_4RUSINTRIN_H
#define MATRUSSE_4RUSINTRIN_H

#include "matrix.h"

matrix_t * createTable(matrix_t * B, int k);
void fillTableIntrin(matrix_t * T, matrix_t * B, int k, int k_);
matrix_t * matrusseIntrin(matrix_t * A, matrix_t * B, int k);

#endif //MATRUSSE_4RUSINTRIN_H
