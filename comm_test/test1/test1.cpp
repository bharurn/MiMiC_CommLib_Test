#include <iostream>
#include <mpi.h>
#include "MessageApi.h"
#include "DataTypes.h"
#include <unistd.h>
#include <cstdlib>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    
    MPI_Comm comm = MPI_COMM_WORLD;
    MCL_init(&comm);
    int rank;
    MPI_Comm_rank(comm, &rank);

    std::cout << "\nServer:"<< numProcs << ':' << rank << '\n';   
    
    if(rank == 0){

		std::cout << "Starting server..\n";
    	MCL_handshake("/p/home/jusers/raghavan1/jureca/CommLib/comm_test/test2/",",", 1);
    	std::cout << "Sending...\n";
    
		int send_data = 25;
    	MCL_send(&send_data, 1, DataType::TYPE_INT, 1); 
		MCL_destroy();
    }
	
    MPI_Finalize();  
}

