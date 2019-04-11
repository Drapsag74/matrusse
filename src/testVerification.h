#ifndef MATRUSSE_TESTVERIFICATION_H
#define MATRUSSE_TESTVERIFICATION_H
#include <stdint.h>

typedef struct matrix_t matrix_t;
struct matrix_t{
    int64_t * value;
    int m; //number of row
    int n; //number of columns
};

//...
int64_t testDiag(matrix_t * A, matrix_t * B, matrix_t * M);

//...
int64_t testMonteCarlo(matrix_t * A, matrix_t * B, matrix_t * M,int64_t a);


#endif //MATRUSSE_TESTVERIFICATION_H