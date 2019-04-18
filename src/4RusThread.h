//
// Created by etien on 17/04/2019.
//

#ifndef MATRUSSE_4RUSTHREAD_H
#define MATRUSSE_4RUSTHREAD_H

#include "matrix.h"
#include "utils.h"
#include <pthread.h>

#define TAILLE_BLOC 4096

struct p_data{
    matrix_t * A;
    matrix_t * B;
    matrix_t * C;
    int k;
    int start;
};





matrix_t * matrusseThread(matrix_t * A, matrix_t * B, int k,int nbCoeur);

static void * worker (void * p_data);

matrix_t * matrusseThreadV2(matrix_t * A, matrix_t * B, int k);

static void * workerV2 (void * p_data2);

void matrusseTestCoeur(matrix_t * A, matrix_t * B,matrix_t * C, int k);

void matrusseTestCoeurV2(matrix_t * A, matrix_t * B,matrix_t * C, int k,int nbCoeur);


#endif //MATRUSSE_4RUSTHREAD_H
