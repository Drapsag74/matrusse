cmake_minimum_required(VERSION 3.10)
project(matrusse)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS  "-mavx -mavx2")
set(CMAKE_CXX_FLAGS "-std=c++11 -msse  -msse2 -msse3 -mavx -mavx2")

add_executable(Matrusse src/main.c src/testVerification.h src/testVerification.c src/fourRussianAlgorithm.c src/fourRussianAlgorithm.h src/matrix.h src/matrix.c src/fourRussianAlgorithmV2.c src/fourRussianAlgorithmV2.h)
add_executable(Test src/test.c src/testVerification.h src/testVerification.c src/matrix.h src/matrix.c src/fourRussianAlgorithmV2.c src/fourRussianAlgorithmV2.h)
add_executable(Tests src/tests/tests.cpp src/tests/tests-matrix.cpp src/matrix.h src/matrix.c)
include_directories( ${MY_SOURCE_DIR}/src)