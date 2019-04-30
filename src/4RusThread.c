//
// Created by etien on 17/04/2019.
//
#include "4RusThread.h"



void matrusseThread(matrix_t * A, matrix_t * B, matrix_t * C, int k,int nbCoeur,int sizeBloc,int version){
    pthread_t threads [nbCoeur];
    struct p_data ** p= malloc(sizeof(struct p_data*)*nbCoeur);

    for(int i = 0; i<nbCoeur;i++){
        p[i]= malloc(sizeof(struct p_data));
        p[i]->A=getBloc(A,i*A->m/nbCoeur,(i+1)*A->m/nbCoeur-1);
        p[i]->B=B;
        p[i]->C=getBloc(C,i*C->m/nbCoeur,(i+1)*C->m/nbCoeur-1);
        p[i]->k=k;
        p[i]->sizeBloc=sizeBloc;
        //m=getBloc(A,i*A->m/2,(i+1)*A->m/2);
        if(version==1){
            pthread_create (&threads[i], NULL, workerV1, p[i]);
        }else if(version==2){
            pthread_create (&threads[i], NULL, workerV2, p[i]);
        }else if(version==3){
            pthread_create (&threads[i], NULL, workerIntrin, p[i]);
        }else if(version==4){
            pthread_create (&threads[i], NULL, workerTest, p[i]);
        }else{
            printf("probleme version");
        }


    }
    for (int i = 0; i < nbCoeur; i++)
    {
        pthread_join (threads[i], NULL);
        free(p[i]->A);
        free(p[i]->C);
        free(p[i]);
    }
    return;
}
static void * workerV1 (void * p_data){
    struct p_data *args = (struct p_data *) p_data;
    //printf("matrice A(%d,%d) et B(%d,%d)",args->A->m,args->A->n,args->B->m,args->B->n);
    matrusseV1(args->A,args->B,args->C,8);
}

static void * workerV2 (void * p_data){
    struct p_data *args = (struct p_data *) p_data;
    //printf("matrice A(%d,%d) et B(%d,%d)",args->A->m,args->A->n,args->B->m,args->B->n);
    matrusseV2(args->A,args->B,args->C,8);
}

static void * workerIntrin (void * p_data){
    struct p_data *args = (struct p_data *) p_data;
    //printf("matrice A(%d,%d) et B(%d,%d)",args->A->m,args->A->n,args->B->m,args->B->n);
    matrusseIntrin(args->A,args->B,args->C,8);
}

static void * workerTest (void * p_data){
    struct p_data *args = (struct p_data *) p_data;
    //printf("matrice A(%d,%d) et B(%d,%d)",args->A->m,args->A->n,args->B->m,args->B->n);
    matrusseV2_1TestBloc(args->A,args->B,args->C,8,128);
}






