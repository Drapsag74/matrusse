#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

#include "matrix.h"
#include "fourRussianAlgorithm.h"


void showHelp() {
    printf("You must give at least one argument for the size of the matrix\n"
           "Matrusse n [m] [-options]\n"
           "Available options are : \n"
           "-b : choose the algorithm you want to test\n"
           "-h : help\n");
}

int64_t bench(char * arg) {

    if(strcmp(arg,"-b=1") == 0) {
        return 1;
    } else {
        return 2;
    }
}



int main(int argc, char *argv[]) {

    if(argc == 1) {
        showHelp();
        return 0;
    }
    int64_t n = 0;
    int64_t  m = 0;
    int64_t bloc = 8;
    int64_t algo = 2;

    if(argc == 2) {
        n = atoi(argv[1]);
        m = n;
    } else if (argc ==3) {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
    } else if (argc >3 || argv[3][0] != '-'){
        n = atoi(argv[1]);
        m = atoi(argv[2]);
        //bloc = atoi(argv[3]);
    }

    int64_t k = 8   ;
    matrix_t * A = aleaMatrixBinaire(n,m);
    matrix_t * B = aleaMatrixBinaire(m, n);
    int64_t * T = createTable(A, k);

    for (int i = 3; i < argc; i++) {
        if(argv[i][0] == '-') {
            switch(argv[i][1]) {
                case 'b' :
                    algo = bench(argv[i]);
                    break;
                case 'm' :
                    algo = 3;
                    break;
            }
        }
    }

    if(algo == 1) {
        printf("exec algo 1\n");
        clock_t t = clock();
        fillTable(T,A,k);
        clock_t t2 = clock();
        printf("Temps d'exec : %d", t2-t);
    }else if(algo == 2) {
        printf("exec algo 2\n");
        clock_t t = clock();
        fillTable2(T, A, k,k);
        clock_t t2 = clock();
        printf("Temps d'exec : %d", t2-t);
    }
    else{
        printf("exec algo matrusse\n");
        clock_t t = clock();
        matrusseV1(A, B, bloc);
        clock_t t2 = clock();
        printf("Temps d'exec : %d", t2-t);
    }
    //showT(T, A->nbColonneInt, k);
    return 0;
}

