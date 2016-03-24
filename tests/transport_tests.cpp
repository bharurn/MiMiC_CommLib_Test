//
// Created by bolnykh on 3/23/16.
//
#define BOOST_TEST_MODULE MyTest
#include "mpi.h"
//#include <BoostTestTargetConfig.h>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
//#include <boost/test/data/monomorphic.hpp>
#include "../transport/Transport.h"
#include "../transport/MPITransport.h"

namespace bdata = boost::unit_test::data;

MPI_Comm small_comm;
bool server;

std::string CLIENT_PATH = "./client1/";
int DATA_SIZE = 3;



std::vector<Transport*> generate_transports() {

    std::vector<Transport*> ret;
    ret.push_back(new MPITransport(MPI_COMM_SELF));
    return ret;
}

void prepare_test() {
    MPI_Init(NULL, NULL);
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    BOOST_TEST(size == 2);
    int color = rank;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &small_comm);
    server = rank == 0;
    if (server) {
        mkdir(CLIENT_PATH.c_str(), 0777);
    }
}

void destroy_test() {
    if (server) {
        rmdir(CLIENT_PATH.c_str());
    }
    MPI_Finalize();
}

BOOST_DATA_TEST_CASE(connect_test,
                     bdata::make(generate_transports()),
                     each_transport) {
    prepare_test();
    Transport* current_transport = dynamic_cast<Transport*>(each_transport);
    int result;
    if (server) {
        current_transport->init_server(CLIENT_PATH, 1);
        result = current_transport->accept_connection(1);
        current_transport->destroy(CLIENT_PATH);
        BOOST_TEST(result == 0);
    } else {
        current_transport->init_client(CLIENT_PATH);
        result = current_transport->connect_address(0);
    }
    destroy_test();
}

/*BOOST_DATA_TEST_CASE(transmit_test,
                     bdata::make(generate_transports()),
                     each_transport) {
    Transport* current_transport = dynamic_cast<Transport*>(each_transport);
    double data[DATA_SIZE];
    for (int j = 0; j < DATA_SIZE; ++j) {
        data[j] = j;
    }

    double received_data[DATA_SIZE];
    int result;
    if (server) {
        current_transport->initServ(&CLIENT_PATH, 1);
        result = current_transport->acceptConnection(1);
        current_transport->sendRawData(&data, TYPE_FLOAT, DATA_SIZE, 1, 0);
        MPI_Barrier(MPI_COMM_WORLD);
        current_transport->closeConnection(1);
        current_transport->destroy(CLIENT_PATH);
    } else {
        current_transport->initClient(CLIENT_PATH);
        result = current_transport->connectAddress(0);
        current_transport->receiveRawData(&received_data, TYPE_FLOAT, DATA_SIZE, 0);
        MPI_Barrier(MPI_COMM_WORLD);
        current_transport->closeConnection(0);
        for (int k = 0; k < DATA_SIZE; ++k) {
            BOOST_TEST(received_data[k] == data[k]);
        }
    }
    destroy_test();
}*/
