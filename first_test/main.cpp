#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    std::cout << numProcs << '\n';
    if (numProcs != 3) {
        std::cout << "The test runs with 3 processes." << std::endl;
	MPI_Abort(MPI_COMM_WORLD, 1);
    }
}

