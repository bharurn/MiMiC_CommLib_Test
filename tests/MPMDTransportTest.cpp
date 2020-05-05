//
// Created by Viacheslav Bolnykh on 06.02.20.
//

#include "gtest/gtest.h"
#include "MPMDTransport.hpp"
#include <mpi.h>

TEST(MPMDTransport, Prepare) {
    MPI_Barrier(MPI_COMM_WORLD);

    MPMDTransport transport(MPI_COMM_WORLD);

    MPI_Comm localComm;
    transport.prepare(&localComm);

    int newSize;
    MPI_Comm_size(localComm, &newSize);

    ASSERT_EQ(2, newSize);
}

TEST(MPMDTransport, InitServer) {
    MPI_Barrier(MPI_COMM_WORLD);

    MPMDTransport transport(MPI_COMM_WORLD);

    int *appnum;
    int flag;
    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_APPNUM, &appnum, &flag);

    MPI_Comm localComm;
    transport.prepare(&localComm);

    if (*appnum == 0) {
        std::vector<std::string> paths{};
        paths.emplace_back("client1");
        if (rank == 1) {
            transport.initServer(paths);
        }
    } else {
        if (rank == 3) {
            transport.initClient("client1");
        }
    }
}

TEST(MPMDTransport, PingPong) {
    MPI_Barrier(MPI_COMM_WORLD);

    MPMDTransport transport(MPI_COMM_WORLD);

    int *appnum;
    int flag;
    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_APPNUM, &appnum, &flag);

    MPI_Comm localComm;
    transport.prepare(&localComm);

    int refData[5] = {5, 4, 3, 2, 1};

    if (*appnum == 0) {
        std::vector<std::string> paths{};
        paths.emplace_back("client1");
        if (rank == 1) {
            transport.initServer(paths);
            transport.sendData(refData, TYPE_INT, 5, 1);
            int testData[5];
            transport.receiveData(testData, TYPE_INT, 5, 1);
            for (int i = 0; i < 5; ++i) {
                ASSERT_EQ(testData[i], refData[i]);
            }
        }
    } else {
        if (rank == 3) {
            transport.initClient("client1");
            int testData[5];
            transport.receiveData(testData, TYPE_INT, 5, 0);
            for (int i = 0; i < 5; ++i) {
                ASSERT_EQ(testData[i], refData[i]);
            }
            transport.sendData(testData, TYPE_INT, 5, 0);
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    if (numProcs != 4) {
        std::cout << "The test runs with 4 processes." << std::endl;
        std::cout << "Current amount of processes " << numProcs << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    MPI_Finalize();
    return 0;
}