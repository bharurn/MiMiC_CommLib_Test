#!/bin/sh

module load Intel/2019.5.281-GCC-8.3.0
module load IntelMPI/2019.3.199
mpiexec -n $1 test1/test1.a > test1.out &
sleep 1
mpiexec -n $1 test2/test2.a > test2.out &
