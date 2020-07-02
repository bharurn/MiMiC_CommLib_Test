#!/usr/local_rwth/bin/zsh

module load intelmpi/2019.3
mpirun -n $1 test1/test1.a : -n $1 test2/test2.a
