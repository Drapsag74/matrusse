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

TEST_CASE( "Matrix", "[matrix]" ) {
        matrix_t * M = nullMatrix(1000, 1000);
        REQUIRE(extract(M, 0, 0, 1) == 1);
}
