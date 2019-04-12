//
// Created by typs on 09/04/19.
//

#include "fourRussianAlgorithm.h"
#include <immintrin.h>

matrix_t * createTable(matrix_t * B, int k){
    int64_t * T = malloc((B->nbColonneInt*sizeof(B->value[0]))<<k);
    matrix_t * result;
    result->nbColonneInt=B->nbColonneInt;
    result->n=B->n;
    result->m=1<<k;
    result->value=T;
    return result;
}

//note : k_ sert à stocker la valeur initiale de k
void fillTable2(matrix_t * T, matrix_t * B, int k, int k_){
    if(k==0)
    {
        for(int i=0;i<B->nbColonneInt;i++)
        {
            writeInt64_t(T,0,i,0);
        }
    }
    else
    {
        fillTable2(T,B,k-1,k_);
        int temp=1<<k-1;
        for(int i=0;i<temp;i++)
        {
            //printf("\n%d\n",i);
            int lim=B->nbColonneInt/4;
            if(lim%4==0)
                lim--;
            for(int j=0;j<=lim;j++)
            {
                //printf("%d ",j):
                //T[(temp+i)*(B->nbColonneInt)+j]=T[i*(B->nbColonneInt)+j]^(B->value[(k_-k)*(B->nbColonneInt)+j]);
                __m256i coeffs=xor_256(T,B,i,k_-k,j);
                if(j!=B->nbColonneInt/4)
                    store_coeffs(T,coeffs,temp+i,j,1);
                else
                    store_coeffs(T,coeffs,temp+i,j,0);
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

__m256i xor_256(matrix_t * A, matrix_t * B, int ARow, int BRow, int Col)
{
    return _mm256_xor_si256(readInt256i(A,ARow,Col),readInt256i(B,BRow,Col));
}

void store_coeffs(matrix_t * R, __m256i coeffs, int Row, int Col, int last)
{
    if(last!=0)
    {
        writeInt64_t(R,Row,Col,coeffs[0]);
        writeInt64_t(R,Row,Col+1,coeffs[1]);
        writeInt64_t(R,Row,Col+2,coeffs[2]);
        writeInt64_t(R,Row,Col+3,coeffs[3]);
    }
    else
    {
        for(int i=0;i<R->nbColonneInt%4;i++)
        {
            writeInt64_t(R,Row,Col+i,coeffs[i]);
        }
    }
}

matrix_t * matrusse(matrix_t * A, matrix_t * B, int k)
{
    matrix_t * result=nullMatrix(A->m,B->n);
    matrix_t * T=createTable(B,k);
    matrix_t * B_;
    for(int i=0;i<A->n/k;i++)
    {
        B_=getBloc(B,i*k,(i+1)*k-1);
        fillTable2(T,B_,k,k);
        for(int j=0;j<A->m;j++)
        {
            int64_t index=extract(A,j,k*i,k);
            int lim=B->nbColonneInt/4;
            if(lim%4==0)
                lim--;
            for(int l=0;l<=lim;l++)
            {
                //result->value[j*B->nbColonneInt+l]=readInt64_t(result,j,l)^T[index*B->nbColonneInt+l];
                __m256i coeffs=xor_256(result,T,j,index,l);
                if(l!=B->nbColonneInt/4)
                    store_coeffs(result,coeffs,j,l,1);
                else
                    store_coeffs(result,coeffs,j,l,0);
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
            int lim=B->nbColonneInt/4;
            if(lim%4==0)
                lim--;
            for(int l=0;l<=lim;l++)
            {
                //result->value[j*B->nbColonneInt+l]=readInt64_t(result,j,l)^T[index*B->nbColonneInt+l];
                __m256i coeffs=xor_256(result,T,j,index,l);
                if(l!=B->nbColonneInt/4)
                    store_coeffs(result,coeffs,j,l,1);
                else
                    store_coeffs(result,coeffs,j,l,0);
            }
        }
        freeBloc(B_);
    }
    freeMatrix(T);
    return result;
}