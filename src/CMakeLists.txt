cmake_minimum_required(VERSION 3.10)
project(matrusse)

set(CMAKE_C_STANDARD 11)

add_executable(Matrusse main.c testVerification.h testVerification.c fourRussianAlgorithm.c fourRussianAlgorithm.h matrix.h matrix.c)
add_executable(Test test.c testVerification.h testVerification.c fourRussianAlgorithm.c fourRussianAlgorithm.h matrix.h matrix.c)
add_executable(Tests tests/tests.cpp)
include_directories( ${MY_SOURCE_DIR}/src)


