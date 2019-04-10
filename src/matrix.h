#ifndef _matrix_h  /* Include guard */
#define _matrix_h
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

matrix_t * nullMatrix(long int m,long int n);

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

//int64_t readInt128i(matrix_t * m,long int indexRow,long int indexColumn);

/**
 *
 * @param m - The matrix
 * @param indexRow - The index of the row of the first bits take
 * @param indexColumn - The index of the column (in int64_t not in bits) of the first bit take
 * @param nbBits - The numbers of bits who need to take
 * @return int64_t - the nbBits selected
 */
int64_t extract(matrix_t * m,long int indexRow,long int indexColumn, int nbBits);

/**
 *
 * @param m - The matrix
 * @return The number of row of the matrix
 */
long int getNbRow(matrix_t * m);

/**
 *
 * @param m - The matrix
 * @return - The number
 */
long int getNbColumn(matrix_t * m);
/**
 *
 * @param m - The matrix
 * @param indexRow - The index of the row return
 * @return return a pointer of the first element of row
 */
int64_t * getRow(matrix_t * m,long int indexRow);

/**
 *
 * @return a random int64_t
 */
int64_t random_64();

#endif
