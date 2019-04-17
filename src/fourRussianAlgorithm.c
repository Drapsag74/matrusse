//
// Created by typs on 09/04/19.
//

#include "fourRussianAlgorithm.h"

matrix_t * matrusseV1(matrix_t * A, matrix_t * B, int k)
{
    printf("matruse classique :\n");
    matrix_t * result=nullMatrix(A->m,B->n);
    int64_t * T=createTable(B,k);
    matrix_t * B_;
    for(int i=0;i<A->n/k;i++)
    {
        B_=getBloc(B,i*k,(i+1)*k-1);
        fillTable2(T,B_,k,k);
        for(int j=0;j<A->m;j++)
        {
            int64_t index=extract(A,j,k*i,k);
            for(int l=0;l<B->nbColonneInt;l++)
            {
                result->value[j*B->nbColonneInt+l]=readInt64_t(result,j,l)^T[index*B->nbColonneInt+l];
            }
        }
        freeBloc(B_);
    }
    free(T);
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
                result->value[j*B->nbColonneInt+l]=readInt64_t(result,j,l)^T[index*B->nbColonneInt+l];
            }
        }
        freeBloc(B_);
        free(T);
    }
    return result;
}