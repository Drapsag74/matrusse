//
// Created by etien on 17/04/2019.
//
#include "4RusThread.h"
#include "fourRussianAlgorithm.h"


matrix_t * matrusseThread(matrix_t * A, matrix_t * B, int k,int nbCoeur){
    printf("matrusse Thread : \n");
    uint32_t m = A->m;
    uint32_t blocksize = TAILLE_BLOC;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;
    matrix_t * C = nullMatrix(m, nbits);
    pthread_t threads [m/blocksize];

    //TODO threading
    for (int start = 0; start < m/blocksize; ++start) {
        progressBar(start,m/blocksize-1);
        struct p_data *args = malloc(sizeof(matrix_t));
        args->A=getBloc(A,start*blocksize,(start+1)*blocksize);
        args->B=B;
        args->C=getBloc(C,start*blocksize,(start+1)*blocksize);
        args->k=k;
        args->start=start;
        pthread_create (&threads, NULL, worker, args);
    }

    for (int i = 0; i < m/blocksize; i++)
    {
        pthread_join (threads[i], NULL);
    }

    uint64_t kReste = k*A->n;
    return C;
}
static void * worker (void * p_data){
    struct p_data *args = (struct p_data *) p_data;
    printf("%d",args->start);
    //progressBar(start,m/blocksize-1);
    for (int i = 0; i < args->A->n/(args->k); ++i) {
        //alocating table of 2^k * B->nbColonneInt
        uint64_t * T = malloc((args->A->nbColonneInt*sizeof(uint64_t))<<args->k);
        matrix_t * Bbloc = getBloc(args->B, i*args->k, i+args->k);
        fillTable(T, Bbloc, args->k);
        for (int s = 0; s < TAILLE_BLOC; ++s) {
            int64_t id = extract(args->A,s, args->k*i, args->k);
            uint64_t * Tline = T+id*args->B->nbColonneInt;
            xorMatrixRow(args->C, s, Tline);
        }
        free(T);/*
        if(args->nbThread==1){
            showMatrix(args->C);
        }*/
        free(Bbloc);
    }



}
/*
matrix_t * matrusseThreadV2TestBloc(matrix_t * A, matrix_t * B, int k,int nbCoeur,int64_t blocSize){
    return
}*/

void matrusseThreadV2(matrix_t * A, matrix_t * B,matrix_t * C, int k,int nbCoeur){

    pthread_t threads [nbCoeur];
    for(int i = 0; i<nbCoeur;i++){
        struct p_data *args = malloc(sizeof(struct p_data));
        args->A=getBloc(A,i*A->m/nbCoeur,(i+1)*A->m/nbCoeur);
        args->B=B;
        args->C=getBloc(C,i*A->m/nbCoeur,(i+1)*A->m/nbCoeur);
        args->k=k;
        //m=getBloc(A,i*A->m/2,(i+1)*A->m/2);
        pthread_create (&threads, NULL, workerV2, args);

    }
    for (int i = 0; i < nbCoeur; i++)
    {
        pthread_join (threads[i], NULL);
    }
    return ;
}

static void * workerV2 (void * p_data){
    struct p_data *args = (struct p_data *) p_data;
    printf("matrice A(%d,%d) et B(%d,%d)",args->A->m,args->A->n,args->B->m,args->B->n);
    matrusseV1(args->A,args->B,args->C,8);
}

/*
void  matrusseTestCoeur(matrix_t * A, matrix_t * B,matrix_t * result, int k)
{
    printf("matruse classique : \n");
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
    return ;
}



void matrusseTestCoeurV2(matrix_t * A, matrix_t * B,matrix_t * C, int k) {
    printf("matruse opti cache :\n");
    uint32_t m = A->m;
    uint32_t blocksize = TAILLE_BLOC;
    uint32_t l = A->n;
    uint32_t n = B->nbColonneInt;
    uint32_t nbits = B->n;

    for (int start = 0; start < m/blocksize; ++start) {
        //progressBar(start,m/blocksize-1);

        for (int i = 0; i < l/k; ++i) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<k);
            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            fillTable(T, Bbloc, k);
            for (int s = 0; s < blocksize; ++s) {
                uint64_t j = start*blocksize + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;
            free(T);
            T = NULL;
        }

        int kReste = l%k;
        if (kReste != 0) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<kReste);
            matrix_t * Bbloc = getBloc(B, l - kReste, kReste);
            fillTable(T, Bbloc, kReste);
            for (int s = 0; s < blocksize; ++s) {
                uint64_t j = start*blocksize + s;
                int64_t id = extract(A,j, l - kReste, kReste);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;
            free(T);
            T = NULL;
        }
    }
    uint64_t blocksizeReste = m%blocksize;
    if(blocksizeReste != 0) {
        int start = m/blocksize;
        for (int i = 0; i < l/k; ++i) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<k);
            matrix_t * Bbloc = getBloc(B, i*k, i+k);
            fillTable(T, Bbloc, k);
            for (int s = 0; s < blocksizeReste; ++s) {
                uint64_t j = start*blocksizeReste + s;
                int64_t id = extract(A,j, k*i, k);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;
            free(T);
            T = NULL;
        }

        int kReste = l%k;
        if (kReste != 0) {
            //alocating table of 2^k * B->nbColonneInt
            uint64_t * T = malloc((n*sizeof(uint64_t))<<kReste);
            matrix_t * Bbloc = getBloc(B, l - kReste, kReste);
            fillTable(T, Bbloc, kReste);
            for (int s = 0; s < blocksizeReste; ++s) {
                uint64_t j = start*blocksizeReste + s;
                int64_t id = extract(A,j, l - kReste, kReste);
                uint64_t * Tline = T+id*n;
                xorMatrixRow(C, j, Tline);
            }
            free(Bbloc);
            Bbloc = NULL;
            free(T);
            T = NULL;
        }
    }
    return ;
}
*/






