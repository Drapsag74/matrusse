//
// Created by Utilisateur on 16/04/2019.
//

#include "4RusIntrin.h"
#include <immintrin.h>

matrix_t * createTable(matrix_t * B, int k){
    uint64_t * T = malloc((B->nbColonneInt*sizeof(B->value[0]))<<k);
    matrix_t * result=matrixVide(1<<k,B->n);
    result->nbColonneInt=B->nbColonneInt;
    result->n=B->n;
    result->m=1<<k;
    result->value=T;
    return result;
}

//note : k_ sert à stocker la valeur initiale de k
void fillTableIntrin(matrix_t * T, matrix_t * B, int k, int k_){
    if(k==0)
    {
        for(int i=0;i<B->nbColonneInt;i++)
        {
            writeInt64_t(T,0,i,0);
        }
    }
    else
    {
        fillTableIntrin(T,B,k-1,k_);
        int temp=1<<k-1;
        for(int i=0;i<temp;i++)
        {
            int lim=B->nbColonneInt/4;
            if(B->nbColonneInt%4==0 && lim!=0)
                lim--;
            for(int j=0;j<=lim;j++)
            {
                __m256i coeffs=_mm256_xor_si256(readInt256i(T,i,j),readInt256i(B,k_-k,j));
                if(j!=B->nbColonneInt/4)
                    _mm256_storeu_si256(&T->value[(temp+i)*(T->nbColonneInt)+4*j],coeffs);
                else
                {
                    for(int l=0;l<T->nbColonneInt%4;l++)
                    {
                        writeInt64_t(T,temp+i,4*j+l,coeffs[l]);
                    }
                }
            }
        }
    }
}

matrix_t * matrusseIntrin(matrix_t * A, matrix_t * B, int k)
{
    matrix_t * result=nullMatrix(A->m,B->n);
    printf("%d\n",A->m);
    printf("%d\n",B->n);
    matrix_t * T=createTable(B,k);
    matrix_t * B_;
    for(int i=0;i<A->n/k;i++)
    {
        if(i%10==0)
            printf("Process %d / %d done\n",i,A->n/k);
        B_=getBloc(B,i*k,(i+1)*k-1);
        fillTableIntrin(T,B_,k,k);
        for(int j=0;j<A->m;j++)
        {
            uint64_t index=extract(A,j,k*i,k);
            int lim=B->nbColonneInt/4;
            if(B->nbColonneInt%4==0 && lim!=0)
                lim--;
            for(int l=0;l<=lim;l++)
            {
                __m256i coeffs=_mm256_xor_si256(readInt256i(result,j,l),readInt256i(T,index,l));
                if(l!=B->nbColonneInt/4)
                    _mm256_storeu_si256(&result->value[j*(result->nbColonneInt)+4*l],coeffs);
                else
                    for(int m=0;m<result->nbColonneInt%4;m++)
                    {
                        writeInt64_t(result,j,4*l+m,coeffs[m]);
                    }
            }
        }
        freeBloc(B_);
    }
    int k_=A->n%k;
    if(k_!=0)
    {
        printf("%d",B->nbColonneInt);
        T=createTable(B,k_);
        B_=getBloc(B,B->m-k_,B->m-1);
        fillTableIntrin(T,B_,k_,k_);
        for(int j=0;j<A->m;j++)
        {
            uint64_t index=extract(A,j,A->n-k_,k_);
            int lim=B->nbColonneInt/4;
            if(B->nbColonneInt%4==0 && lim!=0)
                lim--;
            for(int l=0;l<=lim;l++)
            {
                __m256i coeffs=_mm256_xor_si256(readInt256i(result,j,l),readInt256i(T,index,l));
                if(l!=B->nbColonneInt/4)
                    _mm256_storeu_si256(&result->value[j*(result->nbColonneInt)+4*l],coeffs);
                else
                    for(int m=0;m<result->nbColonneInt%4;m++)
                    {
                        writeInt64_t(result,j,4*l+m,coeffs[m]);
                    }
            }
        }
        freeBloc(B_);
    }
    freeMatrix(T);
    return result;
}
