//
// Created by typs on 09/04/19.
//

#include "fourRussianAlgorithm.h"
#include <immintrin.h>

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

__m256i * createTable(matrix_t * B, int k){
    __m256i * T = _mm_malloc(((B->nbColonneInt/4+1)*sizeof(__m256i)*2)<<k,32);
    //printf("\n%d\n",(B->nbColonneInt/4+1)*4<<k);
    return T;
}

//note : k_ sert à stocker la valeur initiale de k
void fillTable2(__m256i * T, matrix_t * B, int k, int k_){
    if(k==0)
    {
        for(int i=0;i<=B->nbColonneInt/4;i++)
        {
            //T[i]=_mm256_setzero_si256();
            _mm256_storeu_si256(&T[i],_mm256_setzero_si256());
        }
    }
    else
    {
        fillTable2(T,B,k-1,k_);
        //printf("%d",k);
        int temp=1<<k-1;
        for(int i=0;i<temp;i++)
        {
            //printf("\n%d\n",i);
            for(int j=0;j<=B->nbColonneInt/4;j++)
            {
                //printf("\n%d",j);
                //printf("\n%d",((temp+i)*(B->nbColonneInt/4+1)+j));
                //printf("%d ",j);
                //T[(temp+i)*(B->nbColonneInt)+j]=_mm256_xor_si256(T[i*(B->nbColonneInt)+j],readInt256i(B,i,j));
                __m256i temp__=_mm256_loadu_si256(&T[(i*(B->nbColonneInt/4+1)+j)]);
                __m256i temp_=_mm256_xor_si256(temp__,readInt256i(B,i,j));
                _mm256_storeu_si256(&T[((temp+i)*(B->nbColonneInt/4+1)+j)],temp_);
            }
        }
    }
}


void fillTable(int64_t * T, matrix_t * B, int k){
    register int64_t n = B->nbColonneInt;
    for (int i = 0; i < n; i++) {
        T[i] = 0;
    }

    for(int64_t i = 1; i < (1 << k); i++) {
        //printf("%"PRId32",",p);
        int64_t grey = i^(i>>1);
        int64_t greyPrec = (i-1)^((i-1)>>1);
        int64_t log = LOG2(greyPrec^grey);
        //printf("\ngrey : %" PRId64 "greyprec : %" PRId64"dif : %"PRId64 "///// ", grey, greyPrec, dif);

        //printf("\nlog :%"PRId64, log);
        for (int64_t j = 0; j < n; j++) {
            //printf("\nit : %d,%d\n",i,j);
            //printf("\nid : %"PRId64",%"PRId64,i*(B->nbColonneInt), j);
            T[grey*n + j] = T[greyPrec*n + j]^readInt64_t(B,k - log - 1, j);
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

matrix_t * matrusse(matrix_t * A, matrix_t * B, int k)
{
    matrix_t * result=nullMatrix(A->m,B->n);
    __m256i * T=createTable(B,k);
    int nbColT=B->nbColonneInt/4;
    if(B->nbColonneInt%4!=0)
        nbColT++;
    matrix_t * B_;
    for(int i=0;i<A->n/k;i++)
    {
        B_=getBloc(B,i*k,(i+1)*k-1);
        fillTable2(T,B_,k,k);
        for(int j=0;j<A->m;j++)
        {
            int64_t index=extract(A,j,k*i,k);
            for(int l=0;l<=B->nbColonneInt/4;l++)
            {
                __m256i temp_=_mm256_loadu_si256(&T[(index*nbColT+l)]);
                //__m256i temp=_mm256_xor_si256(readInt256i(result,j,l),T[index*nbColT+l]);
                __m256i temp=_mm256_xor_si256(readInt256i(result,j,l),temp_);
                if(l!=B->nbColonneInt/4)
                {
                    result->value[j * B->nbColonneInt + 4*l] = temp[0];
                    result->value[j * B->nbColonneInt + 4*l + 1] = temp[1];
                    result->value[j * B->nbColonneInt + 4*l + 2] = temp[2];
                    result->value[j * B->nbColonneInt + 4*l + 3] = temp[3];
                }
                else
                {
                    for(int p=0;p<B->nbColonneInt %4;p++)
                    {
                        result->value[j * B->nbColonneInt + 4*l+p] = temp[p];
                    }
                }
            }
        }
        freeBloc(B_);
    }
    int k_=A->n%k;
    if(k_!=0)
    {
        T=createTable(B,k_);
        B_=getBloc(B,B->m-k_,B->m-1);
        fillTable2(T,B_,k_,k_);
        for(int j=0;j<A->m;j++)
        {
            int64_t index=extract(A,j,A->n-k_,k_);
            for(int l=0;l<B->nbColonneInt;l++)
            {
                __m256i temp_=_mm256_loadu_si256(&T[(index*nbColT+l)]);
                //__m256i temp=_mm256_xor_si256(readInt256i(result,j,l),T[index*nbColT+l]);
                __m256i temp=_mm256_xor_si256(readInt256i(result,j,l),temp_);
                if(l!=B->nbColonneInt/4)
                {
                    result->value[j * B->nbColonneInt + 4*l] = temp[0];
                    result->value[j * B->nbColonneInt + 4*l + 1] = temp[1];
                    result->value[j * B->nbColonneInt + 4*l + 2] = temp[2];
                    result->value[j * B->nbColonneInt + 4*l + 3] = temp[3];
                }
                else
                {
                    for(int p=0;p<B->nbColonneInt %4;p++)
                    {
                        result->value[j * B->nbColonneInt + 4*l+p] = temp[p];
                    }
                }
            }
        }
        freeBloc(B_);
    }
    return result;
}