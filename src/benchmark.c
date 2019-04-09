//
// Created by Neïlo PERRIN-GANIER on 2019-04-09.
//

#include <python2.7/Python.h>

int main(int argc, char *argv[])
{
    Py_SetProgramName(argv[0]);  /* optional but recommended */
    Py_Initialize();
    Py_Finalize();
    return 0;
}
