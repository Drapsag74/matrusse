#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


Matrice* aleaMatrixBinaire(int m,int n) {


  Matrice *matrice = malloc(sizeof(Matrice));
  int nbColonne=m/(sizeof(long long int)*8);
  printf("%d",nbColonne);

  if(nbColonne*sizeof(long long int)*8==m){
    matrice->matrice = malloc(nbColonne*sizeof(long long int)*n);
    matrice->m=nbColonne;
    matrice->n=n;
  }else{
    matrice->matrice = malloc((nbColonne+1)*sizeof(long long int)*n);
    matrice->m=nbColonne+1;
    matrice->n=n;
  }
  for (int i=0;i<(m/sizeof(long long int))/8*n;i++) {
    printf("r");
    matrice->matrice[i]=rand();
  }
  return matrice;

}
