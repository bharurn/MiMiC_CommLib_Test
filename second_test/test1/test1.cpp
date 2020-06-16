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
     
    std::cout << "\nServer:"<< numProcs << ':' << rank << '\n';   
    
    if(rank == 0){
    	std::cout << "Starting server..\n";
        MCL_init_server("/home/mk115227/tests/CommLib/second_test", ',');
        //sleep(30);
        std::cout << "Sending...\n";
        int send_data = 25;
    	MCL_send(&send_data, 1, DataType::TYPE_INT, 1); 
    }  
}

