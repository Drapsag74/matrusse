//
// Created by etien on 17/04/2019.
//

#ifndef MATRUSSE_4RUSTHREAD_H
#define MATRUSSE_4RUSTHREAD_H

#include "matrix.h"
#include "utils.h"
#include <pthread.h>
#include "fourRussianAlgorithmV2.h"
#include "fourRussianAlgorithm.h"
#include "4RusIntrin.h"

#define TAILLE_BLOC 4096

struct p_data{
    matrix_t * A;
    matrix_t * B;
    matrix_t * C;
    int k;
    int sizeBloc;
};

/**
 *
 * @param A
 * @param B
 * @param C - Matrix result
 * @param k -
 * @param nbCoeur - nb coeur du pc
 * @param sizeBloc - taille de decoupe des bloc si version = 4 ou 2
 * @param version - version de l'algo utiliser
 */
void matrusseThread(matrix_t * A, matrix_t * B, matrix_t * C, int k,int nbCoeur,int sizeBloc,int version);

static void * workerV1 (void * p_data);

static void * workerV2 (void * p_data2);

static void * workerIntrin (void * p_data);

static void * workerTest (void * p_data);
/*
void matrusseTestCoeur(matrix_t * A, matrix_t * B,matrix_t * C, int k);

void matrusseTestCoeurV2(matrix_t * A, matrix_t * B,matrix_t * C, int k);*/


#endif //MATRUSSE_4RUSTHREAD_H
