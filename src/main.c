#include <stdio.h>
#include <stdlib.h>

#define sizeRow = 100

int main(int argc, char *argv[]) {

    //if (argc < 1) {
    //    printf(" put matrix size");
    //}

    printf("%llu",N);

    return 0;

}

addRowFromTable(long long int * C, int indexRowC, long long int * T, int indexRowT) {
    long long int * rowC = C + indexRowC*sizeRow;
    long long int * rowT = T + indexRowT*sizeRow;
    for(int j=0; j<sizeRow/(sizeof(long long int)*8);j++){
        rowC[j] ^= rowT[j];
    }
}

long long int * readBits(long long int * A, int indexRow, int indexColumns, int k) {
    return Atemp = A + indexRow*sizeRow + indexColumns;
}