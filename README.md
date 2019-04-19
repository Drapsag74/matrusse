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
binaries are located in `src`
