#include "matrix.h"
#include "time.h"
#include <limits.h>

matrix_t * aleaMatrixBinaire(long int m,long int n) {
    printf("Creating a matrix of size %dx%d\n", m,n);
    matrix_t *matrice = malloc(sizeof(matrix_t));
    printf("test1");
    matrice->nbColonneInt=n / (sizeof(uint64_t) * 8);
    matrice->m = m;
    matrice->n = n ;

    if (matrice->nbColonneInt * sizeof(uint64_t) * 8 == n) {//The number of Column is a multiple of 64
        matrice->value = malloc(matrice->nbColonneInt * sizeof(uint64_t) * m);
        for (int i = 0; i < m * matrice->nbColonneInt; i++) {
            matrice->value[i] = random_64();
        }
    } else {//The number of column isn't a multiple of 64
        matrice->nbColonneInt++;
        uint64_t mask=0;
        uint64_t tmp;
        for(int i=0;i<matrice->n%64;i++){//Creation of a mask to make the good size of last uint64_t if a line
            tmp=1;
            tmp=tmp<<63-i;
            mask+=tmp;
        }
        matrice->value = malloc((matrice->nbColonneInt) * sizeof(uint64_t) * m);

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
    printf("Creating a matrix null of size %dx%d\n", m,n);
    matrix_t *matrice = malloc(sizeof(matrix_t));
    matrice->nbColonneInt=n / (sizeof(uint64_t) * 8);
    matrice->m = m;
    matrice->n = n ;

    if (matrice->nbColonneInt * sizeof(uint64_t) * 8 == n) {
        matrice->value = malloc(matrice->nbColonneInt * sizeof(uint64_t) * m);
    }else{
        matrice->nbColonneInt++;
        matrice->value = malloc(matrice->nbColonneInt * sizeof(uint64_t) * m);
    }
    for (int i = 0; i < m * matrice->nbColonneInt; i++) {
        matrice->value[i] = 0;
    }
    return matrice;
}

matrix_t * matrixVide(long int m,long int n) {
    printf("Creating a matrix null of size %dx%d\n", m,n);
    matrix_t * matrice = malloc(sizeof(matrix_t));
    matrice->nbColonneInt=n / (sizeof(uint64_t) * 8);
    matrice->m = m;
    matrice->n = n ;
    if(matrice->nbColonneInt*(sizeof(uint64_t) * 8)<n)
        matrice->nbColonneInt++;
    return matrice;
}

matrix_t * identiterMatrix(long int m){//ne pas utiliser
    matrix_t * matrice =nullMatrix(m,m);
    uint64_t * tmp;
    uint64_t mask;
    for(int i=0;i<=matrice->m;i++){
        tmp=getRow(matrice,i);
        mask=1;
        mask=mask<<63-(i%64);

        tmp[i/64]=mask;
    }
    return matrice;
}


void showMatrix(matrix_t * m) {
    printf("[");
    for (int i = 0; i < m->m*m->nbColonneInt; i++) {
        printf("%16"PRIx64" ",m->value[i]);
        if((i+1)%(m->nbColonneInt)==0){
            printf("]\n %d",(i+1)/m->nbColonneInt);
            if(i < m->m*m->nbColonneInt-1){
                printf("[");
            }
        }
    }
}
void showMatrixBits(matrix_t * m) {
    int count;
    uint64_t tmp;
    for (int i = 0; i < m->m*m->nbColonneInt; i++) {
        count=0;
        tmp=m->value[i];
        uint64_t mask=1;
        mask=mask<<63;
        while (tmp) {
            count++;
            if (tmp & mask)
                printf("1 ");
            else
                printf("0 ");

            tmp <<= 1;
        }
        for(int i=count;i<m->n;i++){
            printf("0 ");
        }
        if((i+1)%(m->nbColonneInt)==0){
            printf("\n");
        }
    }
}

uint64_t readInt64_t(matrix_t * m,long int indexRow,long int indexColumns){
    return m->value[indexRow*m->nbColonneInt+indexColumns];
}

__m128i readInt128i(matrix_t * m,long int indexRow,long int indexColumn){
    if(indexColumn*2+1<m->nbColonneInt){
        return _mm_set_epi64x (readInt64_t(m,indexRow,indexColumn*2+1),readInt64_t(m,indexRow,indexColumn*2));
    }else{
        return _mm_set_epi64x (0,readInt64_t(m,indexRow,indexColumn*2));
    }
}

__m256i readInt256i(matrix_t * m,long int indexRow,long int indexColumn){
    if(indexColumn*4+3<m->nbColonneInt){
        return _mm256_loadu_si256(&m->value[indexRow*m->nbColonneInt+indexColumn*4]);
    }else if(indexColumn*4+2<m->nbColonneInt){
        __m256i ret=_mm256_setr_epi64x(m->value[indexRow*m->nbColonneInt+indexColumn*4],m->value[indexRow*m->nbColonneInt+indexColumn*4+1],m->value[indexRow*m->nbColonneInt+indexColumn*4+2],0);
        return ret;
    }else if(indexColumn*4+1<m->nbColonneInt){
        __m256i ret=_mm256_setr_epi64x(m->value[indexRow*m->nbColonneInt+indexColumn*4],m->value[indexRow*m->nbColonneInt+indexColumn*4+1],0,0);

        return ret;
    }else if(indexColumn*4<m->nbColonneInt){
        __m256i ret=_mm256_setr_epi64x(m->value[indexRow*m->nbColonneInt+indexColumn*4],0,0,0);
        return ret;
    }
    printf("problem");
    printf("readInt256i error\n");
    return _mm256_set_epi64x(0,0,0,0);//pas normal
}

void xorMatrixMatrix(matrix_t * m1, long int row1,matrix_t * m2,long int  row2){
    uint64_t * a=getRow(m1,row1);
    uint64_t * b=getRow(m2,row2);
    for(long int i=0;i<m1->nbColonneInt;i++){
        a[i]=a[i]^b[i];
    }

}
void xorMatrixRow(matrix_t * m1, long int row1,uint64_t * row){
    uint64_t * a=getRow(m1,row1);
    for(long int i=0;i<m1->nbColonneInt;i++){
        a[i]=a[i]^row[i];
    }

}


void writeInt64_t(matrix_t * m,long int indexRow,long int indexColumn, uint64_t val){
    m->value[indexRow*m->nbColonneInt+indexColumn]=val;
    return ;
}
void writeInt128i(matrix_t * m,long int indexRow,long int indexColumn, __m128i val){
    if(indexColumn*2<m->nbColonneInt){
        m->value[indexRow*m->nbColonneInt+indexColumn*2]=val[0];
        if(indexColumn*2+1<m->nbColonneInt){
            m->value[indexRow*m->nbColonneInt+indexColumn*2+1]=val[1];
        }
    }
    return ;
}
void writeInt256i(matrix_t * m,long int indexRow,long int indexColumn, __m256i val){
    if(indexColumn*4<m->nbColonneInt){
        m->value[indexRow*m->nbColonneInt+indexColumn*4]=val[0];
        if(indexColumn*4+1<m->nbColonneInt){
            m->value[indexRow*m->nbColonneInt+indexColumn*4+1]=val[1];
            if(indexColumn*4+2<m->nbColonneInt){
                m->value[indexRow*m->nbColonneInt+indexColumn*4+2]=val[2];
                if(indexColumn*4+3<m->nbColonneInt){
                    m->value[indexRow*m->nbColonneInt+indexColumn*4+3]=val[3];
                }
            }
        }
    }
    return ;
}

uint64_t extract(matrix_t * m,long int indexRow,long int indexColumn, int nbBits){
    uint64_t ret=0;
    uint64_t mask=0;
    long int debut=indexColumn/64;
    if(debut==(indexColumn+nbBits-1)/64){//if the number of column is a multiple of 64
        ret =readInt64_t(m,indexRow,debut);
        int emplacement=indexColumn%64;
        for(int i=emplacement;i<emplacement+nbBits;i++){
            uint64_t tmp=1;
            tmp=tmp<<63-i;
            mask+=tmp;
        }
        ret=ret&mask;
        ret=ret>>64-emplacement-nbBits;
    }else{//if the number of column isn't a multiple of 64 (the bits are in two int64_t different)
        //First int64_t---------------------------------------------------------------------------
        uint64_t ret2=readInt64_t(m,indexRow,debut);
        int emplacement=indexColumn%64;
        for(int i=emplacement;i<64;i++){//creation of the first mask
            uint64_t tmp=1;
            tmp=tmp<<63-i;
            mask+=tmp;
        }
        ret2=ret2&mask;
        ret2=ret2<<(emplacement+nbBits)%64;

        //Second int64_t--------------------------------------------------------------------------
        uint64_t ret3=readInt64_t(m,indexRow,debut+1);
        mask=0;
        for(int i=0;i<(emplacement+nbBits)%64;i++){//creation of the second mask
            uint64_t tmp=1;
            tmp=tmp<<63-i;
            mask+=tmp;
        }
        ret3=ret3&mask;
        ret3=ret3>>64-(emplacement+nbBits)%64;

        ret=ret2^ret3;//concatenation of the two int64_t
    }
    return ret;
}

/*int writeFile(matrix_t * m,char * fill){
    fopen()
}*/

long int getNbRow(matrix_t * m){
    return m->m;
}
long int getNbColumn(matrix_t * m){
    return m->nbColonneInt;
}

uint64_t * getRow(matrix_t * m,long int indexRow){
    return m->value+indexRow*m->nbColonneInt;
}

matrix_t * getBloc(matrix_t * m,long int indexFirstRow,long int indexLastRow){
    matrix_t * matrice = malloc(sizeof(matrix_t));
    matrice->m = indexLastRow-indexFirstRow+1;
    matrice->n = m->n ;
    matrice->nbColonneInt=m->nbColonneInt;
    matrice->value=m->value+indexFirstRow*m->nbColonneInt;
    return matrice;
}

uint64_t random_64() {
    /*uint64_t random=rand();
    random=random<<32;
    return  random+rand();*/
    uint64_t random1=(int) ((double)UINT_MAX*((double)rand()/RAND_MAX));
    uint64_t random2=(int) ((double)UINT_MAX*((double)rand()/RAND_MAX));
    random1=random1<<32;
    return random1+random2;
}

void freeBloc(matrix_t * m){
    free(m);
    m=NULL;

}

void freeMatrix(matrix_t * m){
    free(m->value);
    m->value=NULL;

    free(m);
    m=NULL;

}
