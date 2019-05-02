#ifndef MATRUSSE_TESTVERIFICATION_H
#define MATRUSSE_TESTVERIFICATION_H
#include <stdint.h>
#include "matrix.h"

//...
int64_t testDiag(matrix_t * A, matrix_t * B, matrix_t * M);

//...
int64_t testMonteCarlo(matrix_t * A, matrix_t * B, matrix_t * M,int64_t a);


#endif //MATRUSSE_TESTVERIFICATION_H