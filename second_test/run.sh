#!/bin/sh

rm .portname
mpiexec -n 3 test1/test1 > test1.out &
mpiexec -n 3 test2/test2 > test2.out &
