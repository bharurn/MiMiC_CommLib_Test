#include <iostream>
#include <mpi.h>
#include "MessageApi.cpp"
#include "DataTypes.h"
#include <unistd.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::cout << "\nClient:" << numProcs << ':' << rank << '\n';
    
    //sleep(30);

    //std::cout << "Starting client..\n";
    //MCL_init_client("/home/mk115227/tests/CommLib/second_test");
    
    //sleep(10);

    if(rank == 0){
	std::cout << "Starting client..\n";
    	MCL_init_client("/home/mk115227/tests/CommLib/second_test");
        std::cout << "Recieveing..\n";
        int a;
    	MCL_receive(&a, 1, DataType::TYPE_INT, 0);
    	std::cout << a << '\n';
    }  
}

