cmake_minimum_required(VERSION 3.10)
project(matrusse)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS  "-mavx -mavx2 ")
set(CMAKE_CXX_FLAGS "-std=c++11 -msse  -msse2 -msse3 -mavx -mavx2")

add_executable(Matrusse main.c testVerification.h testVerification.c fourRussianAlgorithm.c fourRussianAlgorithm.h matrix.h matrix.c)
add_executable(Test test.c testVerification.h testVerification.c fourRussianAlgorithm.c fourRussianAlgorithm.h matrix.h matrix.c)
add_executable(Tests tests/tests.cpp tests/tests-matrix.cpp matrix.h matrix.c)
include_directories( ${MY_SOURCE_DIR}/src)