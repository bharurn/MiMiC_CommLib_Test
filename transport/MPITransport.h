//
// Created by bolnykh on 23.02.16.
//

#ifndef MIMICCOMMLIB_MPITRANSPORT_H
#define MIMICCOMMLIB_MPITRANSPORT_H


#include "Transport.h"
#include "../DataTypes.h"
#include <mpi.h>

/**
 * Transport implementation using MPI intercommunicators
 */
class MPITransport : public Transport {

    typedef char mpi_port_name[MPI_MAX_PORT_NAME];

public:
    MPITransport(MPI_Comm comm) : Transport(NULL), host_comm(comm) { }

    void initServ(std::string *paths, int client_number);

    void initClient(std::string path);

    void sendMessage(Message *msg, std::string destination);

    void sendRawData(void *data, MPI_Datatype type, int number, int id, int endpoint_id);

    void receiveRawData(void * data_holder, MPI_Datatype type, int count, int id);

    Message *receiveMessage(std::string source);

    Message *receiveMessages(int number, std::string adresses);

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
    static const char* FILENAME;

    /**
     * Array of ports used to connect clients
     */
    mpi_port_name* port;
};


#endif //MIMICCOMMLIB_MPITRANSPORT_H
