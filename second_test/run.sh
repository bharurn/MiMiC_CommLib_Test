#!/bin/sh

rm .portname
mpiexec -n 1 ./test1 > test1.out &
mpiexec -n 1 ./test2 > test2.out &
