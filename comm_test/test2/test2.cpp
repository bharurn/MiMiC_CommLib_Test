#include <iostream>
#include <mpi.h>
#include "MessageApi.cpp"
#include "DataTypes.h"
#include <unistd.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
     
	MPI_Comm comm = MPI_COMM_WORLD;
    MCL_init(&comm);
    int rank;
    MPI_Comm_rank(comm, &rank);

	std::cout << "\nClient:" << numProcs << ':' << rank << '\n';
    
    if(rank == 0){

        std::cout << "Starting client..\n";
    	MCL_handshake("/p/home/jusers/raghavan1/jureca/CommLib/comm_test/test2", ",", 0);
        std::cout << "Receiving..\n";
        int a;
    	
		MCL_receive(&a, 1, DataType::TYPE_INT, 0);
    	std::cout << a << '\n';
		MCL_destroy();
		
    } 
	
    MPI_Finalize(); 
}

