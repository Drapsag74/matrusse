#include <stdint.h>
#include "utils.h"
#include "unistd.h"


int64_t testDiag(matrix_t * A, matrix_t * B, matrix_t * M){
    int8_t b = 1;
    for(int64_t i = 0; i<(A->m); i++){
        int64_t s = 0;
        for(int64_t j = 0; i<(A->n); j++){
            s = s + (readInt64_t(A,i,j)*readInt64_t(B,j,i));
        }
        s = s%2;
        if(s!=readInt64_t(M,i,i)){
            b = 0;
            break;
        }
    }
    return b;
}

int64_t testMonteCarlo(matrix_t * A, matrix_t * B, matrix_t * M,int64_t a) {
    int64_t b = 1;
    for(int64_t i = 0; i<a; i++){
        int64_t s = 0;
        int64_t r1 = (getpid() + rand())%(A->m);
        int64_t r2 = (getpid() + rand())%(A->m);
        for(int64_t j = 0; j<(A->n); j++){
            s = s + (readInt64_t(A,r1,j)*readInt64_t(B,j,r2));
        }
        s=s%2;
        if(s!=readInt64_t(M,r1,r2)){
            b = 0;
            break;
        }
    }
    return b;
}