#ifndef _utils_h  /* Include guard */
#define _utils_h

typedef struct Matrice Matrice;
struct Matrice{
  long long int * matrice;
  int m;
  int n;
};

Matrice * aleaMatrixBinaire(int m,int n);


#endif
