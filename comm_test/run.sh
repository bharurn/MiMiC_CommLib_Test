#!/bin/sh

module load Intel/2019.5.281-GCC-8.3.0
module load IntelMPI/2019.3.199
mpirun -n $1 test1/test1.a : -n $1 test2/test2.a
