#include "stdint.h"
#include "matrix.h"
#include "unistd.h"
#include "time.h"
#include "testVerification.h"

/**
 * /
 * @param A Matrix in dimension nxp
 * @param B Matrix in dimension pxn
 * @param M Matrix (AxB)
 * @return a boolean (1==true / 0==false) if the diagonal of M is true
 */
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

/**
 *
 * @param A Matrix in dimension nxp
 * @param B Matrix in dimension pxn
 * @param M Matrix (AxB)
 * @param a an integer
 * @return a boolean (1==true / 0==false) if the multiplication is true (with probability (1/2)^a)
 */
int64_t testMonteCarlo(matrix_t * A, matrix_t * B, matrix_t * M,int64_t a) {
    int64_t b = 1;
    srand(time(NULL));
    for(int64_t i = 0; i<a; i++){
        int64_t s = 0;
        int64_t r1 = rand()%(A->m);
        int64_t r2 = rand()%(A->m);
        for(int64_t j = 0; j<(A->n); j++){
            s += (extract(A,r1,j,1)*extract(B,j,r2,1));
        }
        s=s%2;
        if(s!=extract(M,r1,r2,1)){
            b = 0;
            break;
        }
    }
    return b;
}