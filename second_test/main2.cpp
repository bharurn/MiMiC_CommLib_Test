#include <iostream>
#include <mpi.h>
#include "MessageApi.cpp"
#include "DataTypes.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    std::cout << numProcs << '\n';
    MCL_init_client("/home/mk115227/tests/CommLib/second_test");
    int a;
    MCL_receive(&a, 1, DataType::TYPE_INT, 0);
    std::cout << a << '\n';   
}

