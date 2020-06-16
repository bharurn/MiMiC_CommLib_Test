#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    std::cout << numProcs << ':' << rank << '\n'; 
    if(rank==0) std::cout << "hello\n";   
}

