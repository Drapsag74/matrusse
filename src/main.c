#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "utils.h"
#include <math.h>

#define sizeRow 128

void addRowFromTable(matrix_t * C, int indexRowC, matrix_t * T, int indexRowT) {
    int64_t * rowC = C->value[indexRowC*C->n];
    int64_t * rowT = T->value[indexRowT*T->n];
    for(int i = 0; i < C->n; i++){
        rowC[i] ^= rowT[i];
    }
}

int64_t * createTable(matrix_t * B, int k){
    int64_t * T = malloc(((B->nbColonneInt)*sizeof(B->value[0]))<<k);
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
        fillTable(T,B,k-1,k_);
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

int main(int argc, char *argv[]) {
    struct matrix_t * m= aleaMatrixBinaire(10,70);
    showMatrix(m);
    /*
    printf("Running test \n");
    matrix_t * A = aleaMatrixBinaire(sizeRow, sizeRow);
    printf("m=%d, n=%d\n", A->m, A->n);

    showMatrix(A, 0, (int)A->m * A->n);
    readInt64_t(A,3,3);*/
    return 0;

}

void addRowFromTable(matrix_t * C, int indexRowC, matrix_t * T, int indexRowT) {
    int64_t * rowC = C->value[indexRowC*C->n];
    int64_t * rowT = T->value[indexRowT*T->n];
    for(int i = 0; i < C->n; i++){
        rowC[i] ^= rowT[i];
    }
}

int64_t * createTable(matrix_t * B, int k){
    int64_t * T = malloc((B->n*sizeof(B->value[0]))<<k);
}

int64_t * fillTable(int64_t * T, matrix_t * B, int k){
    int64_t p = 1 << k;
    for(int i = 0; i < p; i++) {
        printf(PRId64",",(i^(i>>1)));

        //1) calculer la table de gray (T) au fur et a mesure de la boucle grace a la formule ci-dessus
        //2) Trouver que le bit qui change par rapport au code precedent pour savoir quelle ligne de la matrice additionner
        //3) Mettre le résultat de l'addition dans la table T
        //indication: une secode bouble imbriqué devra faire les xor 64 par 64 jusqu'a la fin de la ligne pour l'addition
    }
}
