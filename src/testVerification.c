#include <stdint.h>
#include "utils.h"

int64_t testDiag(matrix_t * A, matrix_t * B, matrix_t * M){
    int8_t b = 1;
    for(int64_t i = 1; i<((A->m)+1); i++){
        int64_t s = 1;
        for(int64_t j = 1; i<((A->n)+1); j++){
            s = s + (readInt64_t(A,j,i)*readInt64_t(B,j,i));
        }
        if(s!=readInt64_t(M,i,i)){
            b = 0;
            break;
        }
    }
    return b;
}