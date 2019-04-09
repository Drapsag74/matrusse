#ifndef _utils_h  /* Include guard */
#define _utils_h
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct matrix_t matrix_t;
struct matrix_t{
  int64_t * value;
  int nbColonneInt;
  int m; //number of row
  int n; //number of columns
};

//...
/**
 *
 * @param m
 * @param n
 * @return struct matrix_t of size (m,n)
 */
matrix_t * aleaMatrixBinaire(long int m,long int n);

/**
 *
 * @param m
 * Print the matrix in a consol
 */
void showMatrix(matrix_t * m);

/**
 *
 * @param m -The matrix
 * @param indexRow - The index of the row
 * @param indexColumn - The index of the column (in int64_t not in bits)
 * @return The int64_t in position (indexRow,indexColumn)
 */
int64_t readInt64_t(matrix_t * m,long int indexRow,long int indexColumn);

/**
 *
 * @param m - The matrix
 * @param indexRow - The index of the row of the first bits take
 * @param indexColumn - The index of the column (in int64_t not in bits) of the first bit take
 * @param nbBits - The numbers of bits who need to take
 * @return int16_t - the nbBits selected
 */
int16_t extract(matrix_t * m,long int indexRow,long int indexColumn, int nbBits);

/**
 *
 * @return a random int64_t
 */
int64_t random_64();

#endif
