//
// Created by bolnykh on 23.02.16.
//

#include "MPITransport.h"

void MPITransport::initServ(int clients_number, std::map<int, Message *> replies) {
    MPI_Open_port(MPI_INFO_NULL, port);

    FILE* port_file = fopen(FILENAME, "w");
    fprintf(port_file, port);
    fclose(port_file);

    MPI_Comm_accept(port, MPI_INFO_NULL, 0, host_comm, &intercomm);
}

void MPITransport::initClient() {
    FILE* port_address = fopen(FILENAME, "r");
    fscanf(port_address, "%s", port);
    fclose(port_address);
    MPI_Comm_connect(port, MPI_INFO_NULL, 0, host_comm, &intercomm);
}

void MPITransport::sendMessage(Message *msg) {

}
