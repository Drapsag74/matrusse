//
// Created by typs on 16/04/19.
//

#include "utils.h"
#include "xoshiro256starstar.h"
#include <time.h>


void fillTable(int64_t * T, matrix_t * B, int k){
    register int64_t n = B->nbColonneInt;
    for (int i = 0; i < n; i++) {
        T[i] = 0;
    }

    for(int64_t i = 1; i < (1 << k); i++) {
        int64_t grey = i^(i>>1);
        int64_t greyPrec = (i-1)^((i-1)>>1);
        int64_t log = LOG2(greyPrec^grey);

        for (int64_t j = 0; j < n; j++) {
            T[grey*n + j] = T[greyPrec*n + j]^readInt64_t(B,k - log - 1, j);
        }

    }
}

//note : k_ sert à stocker la valeur initiale de k
void fillTable2(uint64_t * T, matrix_t * B, int k, int k_){
    uint32_t n = B->nbColonneInt;
    if(k==0) {
        for(int i=0; i < n; i++) {
            T[i] = 0;
        }
    } else {
        fillTable2(T,B,k-1,k_);
        int temp=1<<k-1;
        for(int i=0;i<temp;i++) {
            for(int j=0;j < n;j++) {
                T[(temp + i)*n + j] = T[i*n+j]^readInt64_t(B, k_-k,j);
            }
        }
    }
}



void showT(uint64_t * T, uint64_t size, uint64_t k) {
    printf("Showing table T : \n");
        for (uint64_t j = 0; j < size; j++) {
            for (uint64_t i = 0; i < (1<<k); i++) {
                printf("[");
            printf("%16"PRIx64"\t", T[i*size+j]);
        }
        printf("]");
        printf("\n");
    }
}


int64_t * createTable(matrix_t * B, int k){
    int64_t * T = malloc((B->nbColonneInt*sizeof(B->value[0]))<<k);
    return T;
}

void progressBar(int k, int n)
{
    int temp=(int)((double)k/n*10);
    if(k==0)
        printf("TASK PROGRESS [");
    else
        for(int i=0;i<11;i++)
            printf("\b");
    for(int i=0;i<10;i++)
    {
        if(i<temp)
            printf("|");
        else
            printf(" ");
    }
    printf("]");
    if(k==n)
        printf(" DONE\n");
}

uint64_t random_64()
{
    if(!__my_little_init_was_done)
    {
        srand(time(NULL));
        uint64_t seed[4];
        seed[0]=rand();
        seed[1]=rand();
        seed[2]=rand();
        seed[3]=rand();
        __my_little_xoshiro256starstar_initialization(seed);
        __my_little_init_was_done=1;
        for(int i=0;i<100;i++)
            __my_little_xoshiro256starstar__next();
    }
    return __my_little_xoshiro256starstar__next();
}

void stupidMul(matrix_t * A, matrix_t * B, matrix_t * C)
{
    for(int i=0;i<A->m;i++)
    {
        for(int j=0;j<B->nbColonneInt;j++)
        {
            int64_t s=0;
            for(int64_t k = 0; k<(A->n); k++){
                s += (extract(A,i,k,1)*extract(B,k,j,1));
            }
            writeInt64_t(C,i,j,s);
        }
    }
}