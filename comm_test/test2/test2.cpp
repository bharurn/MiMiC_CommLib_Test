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
	char* mcl_comm = std::getenv("MCL_COMM");
        if (std::stoi(mcl_comm)==1){
                std::cout << "Using old communication mechanism\n";
                MCL_init(nullptr);
        }else{
                std::cout << "Using MPMD\n";
                MPI_Comm comm = MPI_COMM_WORLD;
                MCL_init(&comm);
        }

        std::cout << "Starting client..\n";
    	MCL_init_client("/p/home/jusers/raghavan1/jureca/CommLib/comm_test/test2");
        std::cout << "Recieveing..\n";
        int a;
    	MCL_receive(&a, 1, DataType::TYPE_INT, 0);
    	std::cout << a << '\n';
	MCL_destroy();
    } 
    MPI_Finalize(); 
}

