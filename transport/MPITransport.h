//
// Created by bolnykh on 23.02.16.
//

#ifndef MIMICCOMMLIB_MPITRANSPORT_H
#define MIMICCOMMLIB_MPITRANSPORT_H


#include "Transport.h"
#include "../DataTypes.h"
#include <mpi.h>
#include <iostream>

/**
 * Transport implementation using MPI intercommunicators
 */
class MPITransport : public Transport {

    typedef char mpi_port_name[MPI_MAX_PORT_NAME];

public:
    MPITransport(MPI_Comm comm) : Transport(NULL), host_comm(comm) { }

    void initServ(std::vector<std::string> paths);

    void initClient(std::string path);

    void sendData(void *data, DataType type, int count, int id);

    void receiveData(void *data_holder, DataType type, int count, int id);

    int probe(int id, DataType type);

    int connectAddress(int id);

    int acceptConnection(int id);

    void closeConnection(int id);

    void destroy(std::string path);

    char *getServerAddress();

    MPI_Datatype pick_mpi_type(DataType type);

private:

    /**
     * Communicator to which a remote group will be attached
     */
    MPI_Comm host_comm;

    /**
     * Array of intercommunicators that will handle connections
     */
    MPI_Comm* intercomm;

    /**
     * Name of the file used to share port address
     */
    static std::string FILENAME;

    /**
     * Array of ports used to connect clients
     */
    mpi_port_name* port;
};


#endif //MIMICCOMMLIB_MPITRANSPORT_H
