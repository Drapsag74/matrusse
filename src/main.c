#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

#include "matrix.h"
#include "fourRussianAlgorithm.h"
#include "fourRussianAlgorithmV2.h"
#include "4RusIntrin.h"


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
    }else if(strcmp(arg,"-b=2") == 0){
        return 2;
    }else if(strcmp(arg,"-m=1") == 0){
        return 1;
    }else if(strcmp(arg,"-m=2") == 0){
        return 2;
    }else if(strcmp(arg,"-m=3") == 0){
        return 3;
    }
}



int main(int argc, char *argv[]) {

    if (argc == 1) {
        showHelp();
        return 0;
    }
    int64_t n = 0;
    int64_t m = 0;
    int64_t bloc = 8;
    int64_t algo = 2;
    int64_t blocksize = 1024;
    int64_t fonction = 2;
    int64_t coeur = 4;

    if (argc == 2) {
        n = atoi(argv[1]);
        m = n;
    } else if (argc == 3) {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
    } else if (argc > 3 || argv[3][0] != '-') {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
        bloc = atoi(argv[3]);
    }

    int64_t k = bloc;
    matrix_t * A = aleaMatrixBinaire(n, m);
    matrix_t * B = aleaMatrixBinaire(m, n);
    matrix_t * C = nullMatrix(n,n);
    int64_t * T = createTable(A, k);

    for (int i = 4; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'b' :
                    fonction = 1;
                    switch (argv[i][2]) {
                        case '1' :
                            algo = 1;
                            break;
                        case '2' :
                            algo = 2;
                            break;
                    }
                break;
                case 'm' :
                    switch (argv[i][2]) {
                        case '1' :
                            algo = 1;
                            break;
                        case '2' :
                            algo = 2;
                            if (argc>5){
                              blocksize = atoi(argv[5]);
                            }
                            break;
                        case '3' :
                            algo = 3;
                            break;
                        case '4' :
                            algo = 4;
                            if (argc>5){
                              blocksize = atoi(argv[5]);
                            }
                            break;
                        case '5' :
                            algo = 5;
                            if (argc>5){
                              blocksize = atoi(argv[5]);
                            }
                    }
                break;
                case 't' :
                    fonction = 3;
                    if(argc>5){
                        coeur = atoi(argv[5]);
                    }
                    switch (argv[i][2]) {
                        case '1' :
                            algo = 1;
                            break;
                        case '2' :
                            algo = 2;
                            break;
                        case '3' :
                            algo = 3;
                            break;
                    }
                break;
            }
        }
    }
        if (algo == 1 & fonction == 1) {
            printf("exec algo 1\n");
            clock_t t = clock();
            fillTable(T, A, k);
            clock_t t2 = clock();
            printf("Temps d'exec : %d", (t2 - t)/(CLOCKS_PER_SEC/1000));
        } else if (algo == 2 & fonction == 1) {
            printf("exec algo 2\n");
            clock_t t = clock();
            fillTable2(T, A, k, k);
            clock_t t2 = clock();
            printf("Temps d'exec : %d", (t2 - t)/(CLOCKS_PER_SEC/1000));
        }else if (algo == 1 & fonction == 2) {
            printf("exec algo matrusse V1\n");
            clock_t t = clock();
            matrusseV1(A, B, C, k);
            clock_t t2 = clock();
            printf("Temps d'exec : %d", (t2 - t)/(CLOCKS_PER_SEC/1000));
        } else if (algo == 2 & fonction == 2) {
            printf("exec algo matrusse V2\n");
            clock_t t = clock();
            matrusseV2TestBloc(A ,B ,C ,k ,blocksize);
            clock_t t2 = clock();
            printf("Temps d'exec : %d", (t2 - t)/(CLOCKS_PER_SEC/1000));
        } else if (algo == 3 & fonction == 2) {
            printf("exec algo matrusse V3 Intrin\n");
            clock_t t = clock();
            matrusseIntrin(A,B,C,k);
            clock_t t2 = clock();
            printf("Temps d'exec : %d", (t2 - t)/(CLOCKS_PER_SEC/1000));
        } else if (algo == 4 & fonction == 2) {
            printf("exec algo matrusse Speed of Light\n");
            clock_t t = clock();
            matrusseV2SpeedOfLight(A,B,C,k,blocksize);
            clock_t t2 = clock();
            printf("Temps d'exec : %d", (t2 - t)/(CLOCKS_PER_SEC/1000));
        } else if (algo == 5 & fonction == 2) {
            printf("exec algo matrusse mémoisation\n");
            clock_t t = clock();
            matrusseV2_1TestBloc(A,B,C,k,blocksize);
            clock_t t2 = clock();
            printf("Temps d'exec : %d", (t2 - t)/(CLOCKS_PER_SEC/1000));
        } else if (fonction == 3) {
            printf("exec algo threaded\n");
            clock_t t = clock();
            matrusseThread(A,B,C,k,coeur,blocksize,algo);
            clock_t t2 = clock();
            printf("Temps d'exec : %d", ((t2 - t)/(CLOCKS_PER_SEC/1000))/coeur);
        }
        free(A->value);
        free(A);
        free(B->value);
        free(B);
        free(T);
        free(C->value);
        free(C);
        //showT(T, A->nbColonneInt, k);
        return 0;

}
