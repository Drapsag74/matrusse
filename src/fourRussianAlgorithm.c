//
// Created by typs on 09/04/19.
//

#include "fourRussianAlgorithm.h"
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
            if(B->nbColonneInt%4==0 && lim!=0)
                lim--;
            for(int j=0;j<=lim;j++)
            {
                //printf("%d ",j):
                //T[(temp+i)*(B->nbColonneInt)+j]=T[i*(B->nbColonneInt)+j]^(B->value[(k_-k)*(B->nbColonneInt)+j]);
                //__m256i coeffs=xor_256(T,B,i,k_-k,j);
                __m256i coeffs=_mm256_xor_si256(readInt256i(T,i,j),readInt256i(B,k_-k,j));
                if(j!=B->nbColonneInt/4)
                    //store_coeffs2(T,coeffs,temp+i,j);
                    _mm256_storeu_si256(&T->value[(temp+i)*(T->nbColonneInt)+4*j],coeffs);
                else
                    //store_coeffs(T,coeffs,temp+i,j);
                    for(int i=0;i<T->nbColonneInt%4;i++)
                    {
                        writeInt64_t(T,temp+i,4*j+i,coeffs[i]);
                    }
            }
        }
    }
}


void fillTable(uint64_t * T, matrix_t * B, int k){
    register uint64_t n = B->nbColonneInt;
    for (int i = 0; i < n; i++) {
        T[i] = 0;
    }

    for(uint64_t i = 1; i < (1 << k); i++) {
        //printf("%"PRId32",",p);
        uint64_t grey = i^(i>>1);
        uint64_t greyPrec = (i-1)^((i-1)>>1);
        uint64_t log = LOG2(greyPrec^grey);
        //printf("\ngrey : %" PRId64 "greyprec : %" PRId64"dif : %"PRId64 "///// ", grey, greyPrec, dif);

        //printf("\nlog :%"PRId64, log);
        for (uint64_t j = 0; j < n; j++) {
            //printf("\nit : %d,%d\n",i,j);
            //printf("\nid : %"PRId64",%"PRId64,i*(B->nbColonneInt), j);
            T[grey*n + j] = T[greyPrec*n + j]^readInt64_t(B,k - log - 1, j);
            //printf("\n T : %"PRIx64" T-1 %"PRIx64 " B : %"PRIx64,T[i*(B->nbColonneInt) + j],T[(i - 1)*B->nbColonneInt + j], readInt64_t(B, log, j));
            //printf("\nT[%d] = ",i);
        }

    }
}

void showT(uint64_t * T, uint64_t size, uint64_t k) {
    printf("Showing table T : \n");
    for (uint64_t i = 0; i < (1<<k); i++) {
        printf("[");
        for (uint64_t j = 0; j < size; j++) {
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

void store_coeffs(matrix_t * R, __m256i coeffs, int Row, int Col)
{
    for(int i=0;i<R->nbColonneInt%4;i++)
    {
        writeInt64_t(R,Row,4*Col+i,coeffs[i]);
    }
}

void store_coeffs2(matrix_t * R, __m256i coeffs, int Row, int Col)
{
    _mm256_storeu_si256(&R->value[Row*(R->nbColonneInt)+4*Col],coeffs);
}

matrix_t * matrusse(matrix_t * A, matrix_t * B, int k)
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
        fillTable2(T,B_,k,k);
        for(int j=0;j<A->m;j++)
        {
            uint64_t index=extract(A,j,k*i,k);
            /*if(index<0)
            {
                printf("%16"PRIx64" ",index);
                printf("index=%d j=%d i=%d\n",index,j,i);
                index=-index;
            }*/
            int lim=B->nbColonneInt/4;
            if(B->nbColonneInt%4==0 && lim!=0)
                lim--;
            for(int l=0;l<=lim;l++)
            {
                //result->value[j*B->nbColonneInt+l]=readInt64_t(result,j,l)^T[index*B->nbColonneInt+l];
                //__m256i coeffs=xor_256(result,T,j,index,l);
                __m256i coeffs=_mm256_xor_si256(readInt256i(result,j,l),readInt256i(T,index,l));
                if(l!=B->nbColonneInt/4)
                    //store_coeffs2(result,coeffs,j,l);
                    _mm256_storeu_si256(&result->value[j*(result->nbColonneInt)+4*l],coeffs);
                else
                    //store_coeffs(result,coeffs,j,l);
                    for(int i=0;i<result->nbColonneInt%4;i++)
                    {
                        writeInt64_t(result,j,4*l+i,coeffs[i]);
                    }
            }
        }
        //freeBloc(B_);
    }
    int k_=A->n%k;
    if(k_!=0)
    {
        printf("%d",B->nbColonneInt);
        T=createTable(B,k_);
        B_=getBloc(B,B->m-k_,B->m-1);
        fillTable2(T,B_,k_,k_);
        for(int j=0;j<A->m;j++)
        {
            uint64_t index=extract(A,j,A->n-k_,k_);
            int lim=B->nbColonneInt/4;
            if(B->nbColonneInt%4==0 && lim!=0)
                lim--;
            for(int l=0;l<=lim;l++)
            {
                //result->value[j*B->nbColonneInt+l]=readInt64_t(result,j,l)^T[index*B->nbColonneInt+l];
                //__m256i coeffs=xor_256(result,T,j,index,l);
                __m256i coeffs=_mm256_xor_si256(readInt256i(result,j,l),readInt256i(T,index,l));
                /*if(l!=B->nbColonneInt/4)
                    store_coeffs2(result,coeffs,j,l);
                else
                    store_coeffs(result,coeffs,j,l);*/
                if(l!=B->nbColonneInt/4)
                    //store_coeffs2(result,coeffs,j,l);
                    _mm256_storeu_si256(&result->value[j*(result->nbColonneInt)+4*l],coeffs);
                else
                    //store_coeffs(result,coeffs,j,l);
                    for(int i=0;i<result->nbColonneInt%4;i++)
                    {
                        writeInt64_t(result,j,4*l+i,coeffs[i]);
                    }
            }
        }
        //freeBloc(B_);
    }
    freeMatrix(T);
    return result;
}