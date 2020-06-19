#include <iostream>
#include <mpi.h>
#include "MessageApi.cpp"
#include "DataTypes.h"
#include <unistd.h>
#include <cstdlib>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     
    std::cout << "\nServer:"<< numProcs << ':' << rank << '\n';   
    
    if(rank == 0){
	char* mcl_comm = std::getenv("MCL_COMM");
	if (std::stoi(mcl_comm)==1){	
		std::cout << "Using old communication mechanism\n";
		MCL_init(nullptr);
	}else{
		std::cout << "Using MPMD\n";
		MPI_Comm comm = MPI_COMM_WORLD;
                MCL_init(&comm);
		sleep(1);
	}

	std::cout << "Starting server..\n";
        MCL_init_server("/p/home/jusers/raghavan1/jureca/CommLib/comm_test/test2/", ',');
        std::cout << "Sending...\n";
        int send_data = 25;
    	MCL_send(&send_data, 1, DataType::TYPE_INT, 1); 
	MCL_destroy();
    }
    MPI_Finalize();  
}

