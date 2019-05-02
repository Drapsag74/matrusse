# matrusse
Fast matrix multiplication other GF2 using 4-russians algorithm

## Requirement

* cmake version 3.14
* a c compiler, tested with gcc v8.3.1
* a c++ compiler

## Compilation

* clone the repository and go inside : `git clone https://www.github.com/Drapsag74/matrusse.git && cd matrusse`
* create a new directory for your binary for example : `mkdir bin && cd bin`
* now you can generate the make file by running `cmake -DCMAKE_BUILD_TYPE=Release ..`
* then you can build the binaries by running `make all`, or `make Matrusse` if you only want the Matrusse binary
* binaries are located in `src`

## Execution

* To run the main programm, you have to specify which algorithm you want to try. Then for every algorithm,
* you have to set the proper number of parameters.
* -b to run the filltable algorithms
* -m to run the matrusse algorithms
* -t to run the thread algorithm (not finished)
*
* for example, if you want to do the multiplication of a matrix A (1000x500) with a matrix B (500x1000)
* with the algorithm "matrusseintrin" and a block of size 8 : 
* /Matrusse 1000 500 8 -m3
