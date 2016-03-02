//
// Created by bolnykh on 23.02.16.
//

#include "MPITransport.h"

/*void MPITransport::initServ() {
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
}*/

void MPITransport::initServ() {
    MPI_Open_port(MPI_INFO_NULL, port);

    FILE* port_file = fopen(FILENAME, "w");
    fprintf(port_file, port);
    fclose(port_file);
}

void MPITransport::initClient() {
    Transport::initClient();
}

void MPITransport::sendMessage(Message *msg, std::string destination) {
    Transport::sendMessage(msg, destination);
}

Message *MPITransport::receiveMessage(std::string source) {
    return Transport::receiveMessage(source);
}

Message *MPITransport::receiveMessages(int number, std::string adresses) {
    return Transport::receiveMessages(number, adresses);
}

int MPITransport::connectAddress(std::string address) {
    return Transport::connectAddress(address);
}

int MPITransport::acceptConnection(std::string address) {
    MPI_Comm_accept(port, MPI_INFO_NULL, 0, host_comm, &intercomm);
}

void MPITransport::closeConnection() {
    Transport::closeConnection();
}

char *MPITransport::getServerAddress() {
    return Transport::getServerAddress();
}

void MPITransport::sendRawData(void *data, MPI_Datatype type, int number, int id) {
    MPI_Send(data, number, type, id, MPI_ANY_TAG, intercomm);
}

void *MPITransport::receiveRawData(MPI_Datatype type, int id) {
    MPI_Status status;
    MPI_Probe(id, MPI_ANY_TAG, intercomm, &status);
    int count;
    int size;
    MPI_Get_count(&status, type, &count);
    MPI_Type_size(type, &size);
    void* buf = malloc(size * count);
    MPI_Recv(buf, count, type, id, MPI_ANY_TAG, intercomm, &status);
    return buf;
}
