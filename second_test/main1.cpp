#include <iostream>
#include <mpi.h>
#include "MessageApi.cpp"
#include "DataTypes.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    std::cout << numProcs << '\n';
    int ret = MCL_init_server("/home/mk115227/tests/CommLib/second_test", ',');
    std::cout << ret << '\n';
    int send_data = 25;
    //send_data[0] = 25;
    //std::cout << *send_data << '\n';
    MCL_send(&send_data, 1, DataType::TYPE_INT, 1);   
}

