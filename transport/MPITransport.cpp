//
// Created by bolnykh on 23.02.16.
//

#include <stdexcept>
#include <stdlib.h>
#include "MPITransport.h"

const char* MPITransport::FILENAME = ".portname";

void MPITransport::initServ(std::string *paths, int client_number) {
    port = new mpi_port_name[client_number + 1];
    intercomm = (MPI_Comm *) malloc(sizeof(MPI_Comm) * (client_number + 1));
    for (int i = 0; i < client_number; ++i) {
        MPI_Open_port(MPI_INFO_NULL, port[i + 1]);
        std::string filepath = paths[i] + FILENAME;
        remove(filepath.c_str());
        FILE * port_file = fopen(filepath.c_str(), "w");
        fprintf(port_file, port[i + 1]);
        fclose(port_file);
    }
}

void MPITransport::initClient(std::string path) {
    bool file_exists = false;
    FILE *port_address = NULL;
    std::string port_file = path + FILENAME;
    port = new mpi_port_name[1];
    intercomm = (MPI_Comm *) malloc(sizeof(MPI_Comm));
    while (!file_exists) {
        port_address = fopen(port_file.c_str(), "r");
        if (port_address != NULL) {
            file_exists = true;
        }
    }
    fscanf(port_address, "%s", port[0]);
    fclose(port_address);
}

void MPITransport::sendMessage(Message *msg, std::string destination) {
    throw std::invalid_argument("Invalid function call - use raw data methods instead");
}

Message *MPITransport::receiveMessage(std::string source) {
    throw std::invalid_argument("Invalid function call - use raw data methods instead");
}

Message *MPITransport::receiveMessages(int number, std::string adresses) {
    throw std::invalid_argument("Invalid function call - use raw data methods instead");
}

int MPITransport::connectAddress(int id) {
    MPI_Comm_connect(port[id], MPI_INFO_NULL, 0, host_comm, &intercomm[id]);
    return 0;
}

int MPITransport::acceptConnection(int id) {
    MPI_Comm_accept(port[id], MPI_INFO_NULL, 0, host_comm, &intercomm[id]);
    return 0;
}

void MPITransport::closeConnection(int id) {
    MPI_Comm_disconnect(&intercomm[id]);
}

char *MPITransport::getServerAddress() {
    return port[0];
}

void MPITransport::sendRawData(void *data, DataType type, int number, int id, int endpoint_id) {
    std::cout << "sending data, receiver: " << id << "\n";
    MPI_Ssend(data, number, pick_mpi_type(type), 0, 0, intercomm[id]);
}

void MPITransport::receiveRawData(void * data_holder, DataType type, int count, int id) {
    MPI_Status status;
    MPI_Recv(data_holder, count, pick_mpi_type(type), 0, MPI_ANY_TAG, intercomm[id], &status);
}

int MPITransport::probe(int id, DataType type) {
    int size;
    MPI_Status status;
    MPI_Probe(0, MPI_ANY_TAG, intercomm[id], &status);
    MPI_Get_count(&status, pick_mpi_type(type), &size);
    std::cout << "Size in the queue: " << size << "\n";
    return size;
}

void MPITransport::destroy(std::string path) {
    std::string filepath = path + FILENAME;
    remove(filepath.c_str());
}

MPI_Datatype MPITransport::pick_mpi_type(DataType type) {
    MPI_Datatype send_type;
    switch (type) {
        case TYPE_CHAR:
            send_type = MPI_CHARACTER;
            break;

        case TYPE_INT:
            send_type = MPI_INT;
            break;

        case TYPE_DOUBLE:
            send_type = MPI_DOUBLE;
            break;

        case TYPE_FLOAT:
            send_type = MPI_FLOAT;
            break;

        default:
            send_type = MPI_CHAR;
    }
    return send_type;
}
