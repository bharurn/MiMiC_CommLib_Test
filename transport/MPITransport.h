//
// Created by bolnykh on 23.02.16.
//

#ifndef MIMICCOMMLIB_MPITRANSPORT_H
#define MIMICCOMMLIB_MPITRANSPORT_H


#include "Transport.h"
#include <mpi.h>

/**
 * Transport implementation using intercommunicators
 */
class MPITransport : public Transport {

public:
    MPITransport(MPI_Comm comm) : Transport(NULL), host_comm(comm) { }


    void initServ();

    void initClient();

    void sendMessage(Message *msg, std::string destination);

    void sendRawData(void* data, MPI_Datatype type, int number, int id);

    void* receiveRawData(MPI_Datatype type, int id);

    Message *receiveMessage(std::string source);

    Message *receiveMessages(int number, std::string adresses);

    int connectAddress(std::string address);

    int acceptConnection(std::string address);

    void closeConnection();

    char *getServerAddress();

private:
    MPI_Comm host_comm;
    MPI_Comm intercomm;
    const char* FILENAME = ".portname";
    char port[MPI_MAX_PORT_NAME];
};


#endif //MIMICCOMMLIB_MPITRANSPORT_H
