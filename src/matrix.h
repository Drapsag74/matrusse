#ifndef _matrix_h  /* Include guard */
#define _matrix_h
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <emmintrin.h>
#include <immintrin.h>

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
 * @param m - The number of row
 * @param n - The number of column
 * @return struct matrix_t of size (m,n)
 */
matrix_t * aleaMatrixBinaire(long int m,long int n);

/**
 *
 * @param m - The number of row
 * @param n - The number of column
 * @return a matrix whise all bits = 0
 */
matrix_t * nullMatrix(long int m,long int n);

/**
 *
 * @param m - The size of the matrix
 * @return
 */

matrix_t * identiterMatrix(long int m);

matrix_t * matrixVide(long int m,long int n);

void xorMatrixMatrix(matrix_t * m1, long int row1,matrix_t * m2,long int  row2);

void xorMatrixRow(matrix_t * m1, long int row1,int64_t * row);

/**
 *
 * @param m
 * Print the matrix in a consol
 */
void showMatrix(matrix_t * m);

/**
 * Show the matrix whise 1 or 0
 * @param m - The matrix
 */
void showMatrixBits(matrix_t * m);

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
 * @param indexRow - The index of the row
 * @param indexColumn - The index of the column
 * @return
 */
__m128i readInt128i(matrix_t * m,long int indexRow,long int indexColumn);

/**
 *
 * @param m - The matrix
 * @param indexRow - The index of the row
 * @param indexColumn - The index of the column
 * @return
 */
__m256i readInt256i(matrix_t * m,long int indexRow,long int indexColumn);

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

void writeInt64_t(matrix_t * m,long int indexRow,long int indexColumn, int64_t val);

void writeInt128i(matrix_t * m,long int indexRow,long int indexColumn, __m128i val);

void writeInt256i(matrix_t * m,long int indexRow,long int indexColumn, __m256i val);


/**
 *
 * @param m - The matrix
 * @param indexFirstRow - The index of the first row of the bloc
 * @param indexLastRow - The index of the last row of the bloc
 * @return
 */
matrix_t * getBloc(matrix_t * m,long int indexFirstRow,long int indexLastRow);

/**
 *
 * @return a random int64_t
 */
int64_t random_64();

/**
 *
 * @param m - The Bloc who need to be free
 */
void freeBloc(matrix_t * m);

/**
 *
 * @param m - The Matrix who need to be free
 */
void freeMatrix(matrix_t * m);

#endif
