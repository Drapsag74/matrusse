cmake_minimum_required(VERSION 3.10)
project(matrusse C)

set(CMAKE_C_STANDARD 11)

add_executable(Matrusse main.c testVerification.h testVerification.c fourRussianAlgorithm.c fourRussianAlgorithm.h)
include_directories( ${MY_SOURCE_DIR}/src)
add_library(utils matrix.h matrix.c)
target_link_libraries (Matrusse utils)