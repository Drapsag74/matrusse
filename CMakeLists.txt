cmake_minimum_required(VERSION 3.10)
project(matrusse)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS  "-mavx -mavx2 -pthread")
set(CMAKE_CXX_FLAGS "-std=c++11 -msse  -msse2 -msse3 -mavx -mavx2 ")


include_directories( ${MY_SOURCE_DIR}/src)
add_subdirectory(src)