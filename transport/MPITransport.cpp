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
    bool file_exists = false;
    FILE *port_address = NULL;
//    while (!file_exists) {
        port_address = fopen(FILENAME, "r");
        if (port_address != NULL) {
            file_exists = true;
        }
//    }
    fscanf(port_address, "%s", port);
    fclose(port_address);
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
    MPI_Comm_connect(port, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
}

int MPITransport::acceptConnection(std::string address) {
    MPI_Comm_accept(port, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
}

void MPITransport::closeConnection() {
    MPI_Comm_disconnect(&intercomm);
}

char *MPITransport::getServerAddress() {
    return port;
}

void MPITransport::sendRawData(void *data, MPI_Datatype type, int number, int id, int endpoint_id) {
    MPI_Ssend(data, number, type, 0, endpoint_id, intercomm);
}

RawDataStruct * MPITransport::receiveRawData(MPI_Datatype type, int id) {
    MPI_Status status;
    MPI_Probe(0, id, intercomm, &status);
    int count;
    int size;
    MPI_Get_count(&status, type, &count);
    MPI_Type_size(type, &size);
    void* buf = malloc(size * count);
    MPI_Recv(buf, count, type, 0, id, intercomm, &status);
    RawDataStruct* dataStruct = new RawDataStruct;
    dataStruct->data = buf;
    dataStruct->count = count;
    return dataStruct;
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
