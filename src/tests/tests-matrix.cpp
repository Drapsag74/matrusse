//
// Created by typs on 11/04/19.
//
#include "catch.hpp"

extern "C" {
    #include "../matrix.h"
}


unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}


TEST_CASE( "Factorials are computed", "[factorial]" ) {
REQUIRE( Factorial(1) == 1 );
REQUIRE( Factorial(2) == 2 );
REQUIRE( Factorial(3) == 6 );
REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "Matrix nulle puissance 2", "[matrix]" ) {
        matrix_t * M = nullMatrix(512, 512);
        for(int i=0;i<(512*M->nbColonneInt);i++) {
            REQUIRE(M->value[i] == 0);
        }
            REQUIRE(M->m==512);
            REQUIRE(M->n==512);
            REQUIRE(M->nbColonneInt==8);
}

TEST_CASE("Showmatrix","[matrice]"){
    matrix_t * M = nullMatrix(4,4);
    for(int i=0;i<(4*M->nbColonneInt);i++) {
        if(i%2==1){
            M->value[i]=64;
        }
    }
   // showMatrix(M);
}

TEST_CASE("readInt","[matrice]"){
    matrix_t * M = nullMatrix(64, 128);
    writeInt64_t(M,22,1,48);
    writeInt64_t(M,60,0,84);
    CHECK(readInt64_t(M,22,1)==48);
    CHECK(readInt64_t(M,60,0)==84);
}

