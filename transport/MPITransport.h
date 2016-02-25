//
// Created by bolnykh on 23.02.16.
//

#ifndef MIMICCOMMLIB_MPITRANSPORT_H
#define MIMICCOMMLIB_MPITRANSPORT_H


#include "Transport.h"
#include <mpi.h>

class MPITransport : public Transport {

public:
    MPITransport(MPI_Comm comm) : Transport(NULL), host_comm(comm) { }


    virtual void initServ(int clients_number, std::map<int, Message *> replies) override;

    virtual void initClient() override;

    virtual void sendMessage(Message *msg) override;

private:
    MPI_Comm host_comm;
    MPI_Comm intercomm;
    const char* FILENAME = ".portname";
    char port[MPI_MAX_PORT_NAME];
};


#endif //MIMICCOMMLIB_MPITRANSPORT_H
