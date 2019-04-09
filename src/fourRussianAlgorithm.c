//
// Created by typs on 09/04/19.
//

#include "fourRussianAlgorithm.h"

matrix_t *  MethodFourRussianMultiplication(matrix_t * A, matrix_t * B, int32_t k) {
    matrix_t * C = malloc(sizeof(matrix_t));

    return C;
}

void addRowFromTable(matrix_t * C, int indexRowC, matrix_t * T, int indexRowT) {
    int64_t * rowC = C->value + indexRowC*C->n;
    int64_t * rowT = T->value + indexRowT*T->n;
    for(int i = 0; i < C->n; i++){
        rowC[i] ^= rowT[i];
    }
}

int64_t * createTable(matrix_t * B, int k){
    int64_t * T = malloc((B->nbColonneInt*sizeof(B->value[0]))<<k);
    return T;
}

//note : k_ sert à stocker la valeur initiale de k
void fillTable2(int64_t * T, matrix_t * B, int k, int k_){
    if(k==0)
    {
        for(int i=0;i<B->nbColonneInt;i++)
        {
            T[i]=0;
        }
    }
    else
    {
        fillTable2(T,B,k-1,k_);
        int temp=1<<k-1;
        for(int i=0;i<temp;i++)
        {
            //printf("\n%d\n",i);
            for(int j=0;j<B->nbColonneInt;j++)
            {
                //printf("%d ",j):
                T[(temp+i)*(B->nbColonneInt)+j]=T[i*(B->nbColonneInt)+j]^(B->value[(k_-k)*(B->nbColonneInt)+j]);
            }
        }
    }
}


void fillTable(int64_t * T, matrix_t * B, int k){
    int64_t p = 1 << k;
    for (int i = 0; i < B->nbColonneInt; i++) {
        T[i] = 0;
    }

    for(int64_t i = 1; i < p; i++) {
        //printf("%"PRId32",",p);
        int64_t grey = i^(i>>1);
        int64_t greyPrec = (i-1)^((i-1)>>1);
        int64_t dif = grey^greyPrec;
        int64_t log = 0;
        //printf("\ngrey : %" PRId64 "greyprec : %" PRId64"dif : %"PRId64 "///// ", grey, greyPrec, dif);
        while(dif > 1) {
            dif = dif >>1;
            log++;
        }
        //printf("\nlog :%"PRId64, log);
        for (int64_t j = 0; j < B->nbColonneInt; j++) {
            //printf("\nit : %d,%d\n",i,j);
            //printf("\nid : %"PRId64",%"PRId64,i*(B->nbColonneInt), j);
            T[grey*(B->nbColonneInt) + j] = T[greyPrec*B->nbColonneInt + j]^readInt64_t(B,k - log - 1, j);
            //printf("\n T : %"PRIx64" T-1 %"PRIx64 " B : %"PRIx64,T[i*(B->nbColonneInt) + j],T[(i - 1)*B->nbColonneInt + j], readInt64_t(B, log, j));
            //printf("\nT[%d] = ",i);
        }

    }
}

void showT(int64_t * T, int64_t size, int64_t k) {
    printf("Showing table T : \n");
    for (int64_t i = 0; i < (1<<k); i++) {
        printf("[");
        for (int64_t j = 0; j < size; j++) {
            printf("%16"PRIx64"\t", T[i*size+j]);
        }
        printf("]");
        printf("\n");
    }
}
