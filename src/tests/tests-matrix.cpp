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
    #include "../fourRussianAlgorithm.h"
    #include "../testVerification.h"
    #include "../fourRussianAlgorithmV2.h"
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
    uint64_t *c = getRow(M,2);
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
        uint64_t *a = getRow(M,10+i);
        uint64_t *b = getRow(N,i);
        CHECK(a[0]==b[0]);
    }
}

TEST_CASE("extract","[matrice]"){
    matrix_t * M = nullMatrix(15, 128);
    writeInt64_t(M,3,0,0x7530000000000000);
    writeInt64_t(M,5,0,4);
    writeInt64_t(M,7,0,5);
    writeInt64_t(M,9,0,6);
    writeInt64_t(M,11,0,7);
    writeInt64_t(M,13,0,8);
    writeInt64_t(M,3,1,13);
    writeInt64_t(M,5,1,14);
    writeInt64_t(M,7,1,15);
    writeInt64_t(M,9,1,16);
    writeInt64_t(M,11,1,17);
    writeInt64_t(M,13,1,18);
    REQUIRE(extract(M,3,64,64)==13);
    REQUIRE(extract(M,3,0,16)==0x7530);
    REQUIRE(extract(M,5,64,64)==14);
    REQUIRE(extract(M,5,0,64)==4);
    REQUIRE(extract(M,7,64,64)==15);
    REQUIRE(extract(M,7,0,64)==5);
}

TEST_CASE("TEST montecarlo matrusseV1","[matrice]"){
    matrix_t * A = aleaMatrixBinaire(1024,1024);
    matrix_t * C = aleaMatrixBinaire(1024,1024);
    matrix_t * B = identiterMatrix(1024);
    matrix_t * M = matrusseV1(A,B,1);
    matrix_t * N = matrusseV1(A,C,5);
    int64_t r = testMonteCarlo(A,B,M,20);
    int64_t r2 = testMonteCarlo(A,C,N,20);
    REQUIRE(r==1);
    REQUIRE(r2==1);

}

TEST_CASE("TEST montecarlo matrusseV2","[matrice]"){
    matrix_t * A = aleaMatrixBinaire(2048,2048);
    matrix_t * C = aleaMatrixBinaire(2048,2048);
    matrix_t * B = identiterMatrix(2048);
    matrix_t * M = matrusseV2(A,B,1);
    matrix_t * N = matrusseV2(A,C,5);
    int64_t r = testMonteCarlo(A,B,M,20);
    int64_t r2 = testMonteCarlo(A,C,N,20);
    REQUIRE(r==1);
    REQUIRE(r2==1);

}

TEST_CASE("test du testMonteCarlo","[matrice]"){
    matrix_t * A = nullMatrix(3,3);
    matrix_t * B = nullMatrix(3,3);
    writeInt64_t(A,0,0,0xa000000000000000);
    writeInt64_t(A,1,0,0xc000000000000000);
    writeInt64_t(A,2,0,0x2000000000000000);
    writeInt64_t(B,0,0,0xc000000000000000);
    writeInt64_t(B,1,0,0x4000000000000000);
    writeInt64_t(B,2,0,0xa000000000000000);
    matrix_t * M = matrusseV1(A,B,1);
    for(int64_t i = 0; i<5; i++) {
        int s = 0;
        int sb = 0;
        int64_t r1 = rand() % (A->m);
        int64_t r2 = rand() % (A->m);
        for (int64_t j = 0; j < (A->n); j++) {
            uint64_t a = extract(B, j, r2, 1);
            uint64_t b = extract(A, r1, j, 1);
            s += a * b;
        }
        sb = s % 2;
    }
}

