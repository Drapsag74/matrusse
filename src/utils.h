#ifndef _utils_h  /* Include guard */
#define _utils_h
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct matrix_t matrix_t;
struct matrix_t{
  int64_t * value;
  int m; //number of row
  int n; //number of columns
};

//...
matrix_t * aleaMatrixBinaire(int m,int n);

//...
void showMatrix(matrix_t * M/*, unsigned int start, unsigned int end*/);

//...
int64_t readInt64_t(matrix_t * A, int indexRow, int indexColumns);

#endif
