//
// Created by typs on 11/04/19.
//
#include <sstream>
#include <iostream>
#include <immintrin.h>
#include <emmintrin.h>
#include "catch.hpp"

extern "C" {
    #include "../matrix.h"
}

using namespace std;

TEST_CASE( "Matrix nulle puissance 2", "[matrix]" ) {
        matrix_t * M = nullMatrix(512, 512);
        for(int i=0;i<(512*M->nbColonneInt);i++) {
            REQUIRE(M->value[i] == 0);
        }
            REQUIRE(M->m==512);
            REQUIRE(M->n==512);
            REQUIRE(M->nbColonneInt==8);
}

/* TEST_CASE("Showmatrix","[matrice]"){
    matrix_t * M = nullMatrix(4,4);
    for(int i=0;i<(4*M->nbColonneInt);i++) {
        if(i%2==1){
            M->value[i]=64;
        }
    }
   stringstream test;

    showMatrix(M);
    test << std::cout;
    std::cout << test;
} */

TEST_CASE("read/write Int","[matrice]"){
    matrix_t * M = nullMatrix(64, 256);
    writeInt64_t(M,22,1,48);
    writeInt64_t(M,60,0,84);
    __m128i a = _mm_set_epi64x(45,14);
    __m256i b = _mm256_set_epi64x(4,6,9,11);
    writeInt128i(M,18,1,a);
    writeInt256i(M,25,0,b);
    CHECK(readInt64_t(M,22,1)==48);
    CHECK(readInt64_t(M,60,0)==84);
    CHECK(readInt128i(M,18,1)[0]==14);
    CHECK(readInt128i(M,18,1)[1]==45);
    CHECK(readInt256i(M,25,0)[0]==11);
    CHECK(readInt256i(M,25,0)[1]==9);
    CHECK(readInt256i(M,25,0)[2]==6);
    CHECK(readInt256i(M,25,0)[3]==4);
}

TEST_CASE("nbrow/column","[matrice]"){
    matrix_t * M = aleaMatrixBinaire(512, 512);
    matrix_t * N = nullMatrix(66, 66);
    int64_t *c = getRow(M,2);
    CHECK(getNbRow(M)==512);
    CHECK(getNbColumn(M)==(512/64));
    CHECK(getNbRow(N)==66);
    CHECK(getNbColumn(N)==(2));
    CHECK(c[0]==readInt64_t(M,2,0));
}

TEST_CASE("Getblock","[matrice]"){
    matrix_t * M = aleaMatrixBinaire(512,512);
    matrix_t * N = getBloc(M,10,20);
    REQUIRE(getNbRow(N)==11);
    for(int i = 0; i<getNbRow(N);i++){
        int64_t *a = getRow(M,10+i);
        int64_t *b = getRow(N,i);
        CHECK(a[0]==b[0]);
    }
}



