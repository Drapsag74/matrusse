#include "matrix.h"
#include "time.h"
#include <emmintrin.h>

matrix_t * aleaMatrixBinaire(long int m,long int n) {
    printf("Creating a matrix of size %dx%d\n", m,n);
    matrix_t *matrice = malloc(sizeof(matrix_t));
    matrice->nbColonneInt=n / (sizeof(long long int) * 8);
    int nbInt=0;
    matrice->m = m;
    matrice->n = n ;

    if (matrice->nbColonneInt * sizeof(long long int) * 8 == n) {//The number of Column is a multiple of 64
        matrice->value = malloc(matrice->nbColonneInt * sizeof(long long int) * m);
        for (int i = 0; i < m * matrice->nbColonneInt; i++) {
            matrice->value[i] = random_64();
        }
    } else {//The number of column isn't a multiple of 64
        matrice->nbColonneInt++;
        int64_t mask=0;
        int64_t tmp;
        for(int i=0;i<matrice->n%64;i++){//Creation of a mask to make the good size of last int64_t if a line
            tmp=1;
            tmp=tmp<<63-i;
            mask+=tmp;
        }
        matrice->value = malloc((matrice->nbColonneInt) * sizeof(long long int) * m);

        for (int i = 0; i < m * matrice->nbColonneInt; i++) {
            matrice->value[i] = random_64();
            if((i+1)%(matrice->nbColonneInt)==0){
                matrice->value[i] =matrice->value[i] & mask;
            }
        }
    }

    return matrice;

}
matrix_t * nullMatrix(long int m,long int n) {
    printf("Creating a matrix of size %dx%d\n", m,n);
    matrix_t *matrice = malloc(sizeof(matrix_t));
    matrice->nbColonneInt=n / (sizeof(long long int) * 8);
    matrice->m = m;
    matrice->n = n ;

    if (matrice->nbColonneInt * sizeof(long long int) * 8 == n) {
        matrice->value = malloc(matrice->nbColonneInt * sizeof(long long int) * m);
    }else{
        matrice->nbColonneInt++;
    }
    for (int i = 0; i < m * matrice->nbColonneInt; i++) {
        matrice->value[i] = 0;
    }
    return matrice;
}


void showMatrix(matrix_t * m) {
    printf("[");
    for (int i = 0; i < m->m*m->nbColonneInt; i++) {
        printf("%16"PRIx64" ",m->value[i]);
        if((i+1)%(m->nbColonneInt)==0){
            printf("]\n");
            if(i < m->m*m->nbColonneInt-1){
                printf("[");
            }
        }
    }
}

int64_t readInt64_t(matrix_t * m,long int indexRow,long int indexColumns){
    return m->value[indexRow*m->nbColonneInt+indexColumns];
}

/*int64_t readInt128i(matrix_t * m,long int indexRow,long int indexColumn){
    return
}*/

int64_t extract(matrix_t * m,long int indexRow,long int indexColumn, int nbBits){
    int64_t ret=0;
    int64_t mask=0;
    long int debut=indexColumn/64;
    if(debut==(indexColumn+nbBits)/64){//if the number of column is a multiple of 64
        ret =readInt64_t(m,indexRow,debut);
        int emplacement=indexColumn%64;
        for(int i=emplacement;i<emplacement+nbBits;i++){
            int64_t tmp=1;
            tmp=tmp<<63-i;
            mask+=tmp;
        }
        ret=ret&mask;
        ret=ret>>64-emplacement-nbBits;
    }else{//if the number of column isn't a multiple of 64 (the bits are in two int64_t different)
        //First int64_t---------------------------------------------------------------------------
        int64_t ret2=readInt64_t(m,indexRow,debut);
        int emplacement=indexColumn%64;
        for(int i=emplacement;i<64;i++){//creation of the first mask
            int64_t tmp=1;
            tmp=tmp<<63-i;
            mask+=tmp;
        }
        ret2=ret2&mask;
        ret2=ret2<<(emplacement+nbBits)%64;

        //Second int64_t--------------------------------------------------------------------------
        int64_t ret3=readInt64_t(m,indexRow,debut+1);
        mask=0;
        for(int i=0;i<(emplacement+nbBits)%64;i++){//creation of the second mask
            int64_t tmp=1;
            tmp=tmp<<63-i;
            mask+=tmp;
        }
        ret3=ret3&mask;
        ret3=ret3>>64-(emplacement+nbBits)%64;

        ret=ret2^ret3;//concatenation of the two int64_t
    }
    return ret;
}

long int getNbRow(matrix_t * m){
    return m->m;
}
long int getNbColumn(matrix_t * m){
    return m->nbColonneInt;
}

int64_t * getRow(matrix_t * m,long int indexRow){
    return m->value[indexRow*m->nbColonneInt];
}

int64_t random_64() {
    int64_t random=rand();
    random=random<<32;
    return  random+rand();
}

