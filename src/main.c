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
    int64_t algo = 2;

    if(argc == 2) {
        n = atoi(argv[1]);
        m = n;
    } else if (argc > 2 || argv[2][0] != '-') {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
    }

    int64_t k = n;
    matrix_t * A = aleaMatrixBinaire(n,m);
    int64_t * T = createTable(A, k);

    for (int i = 2; i < argc; i++) {
        if(argv[i][0] == '-') {
            switch(argv[i][1]) {
                case 'b' :
                    algo = bench(argv[i]);
            }
        }
    }

    if(algo == 1) {
        printf("exec algo 1");
        clock_t t = clock();
        fillTable(T,A,k);
        clock_t t2 = clock();
        printf("Temps d'exec : %d", t2-t);
    } else {
        clock_t t = clock();
        fillTable2(T, A, k,k);
        clock_t t2 = clock();
        printf("Temps d'exec : %d", t2-t);
    }

    return 0;

}

