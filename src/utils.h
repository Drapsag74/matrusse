#ifndef _utils_h  /* Include guard */
#define _utils_h

typedef struct Matrice Matrice;
struct Matrice{
  long long int * value;
  int m; //number of row
  int n; //number of columns
};

Matrice * aleaMatrixBinaire(int m,int n);
void showMatrix(Matrice * M, unsigned int start, unsigned int end);

#endif
