//
// Created by bolnykh on 12/7/15.
//

#ifndef MIMICCOMMLIB_MESSAGESERVICE_H
#define MIMICCOMMLIB_MESSAGESERVICE_H


#include "transport/Transport.h"
#include "transport/Client.h"
#include "transport/Server.h"
#include "transport/MPITransport.h"

/**
 * External API of the library
 * NOTE! ALL API CALLS ARE BLOCKING!!!
 */

Endpoint* endpoint;

/**
 * Use to initialize the server
 *
 * \param clients_number number of clients to be connected
 * \param paths local paths of all clients (needed for addresses sharing)
 */
int MCL_init_server(int clients_number, char **paths) {
    Transport* protocol = new MPITransport(MPI_COMM_SELF);
    Server* server = new Server(protocol);
    server->setId(0);
    std::string* client_paths = new std::string[clients_number];
    for (int i = 0; i < clients_number; ++i) {
        client_paths[i] = std::string(paths[i]);
    }
    endpoint = server;
    server->init(clients_number, client_paths);
    server->handshake();
    return 0;
}

/**
 * Initialize client endpoint
 *
 * \param path string containing the path in the file system to this client
 */
int MCL_init_client(char *path) {
    Transport* protocol = new MPITransport(MPI_COMM_SELF);
    std::string client_path = std::string(path);
    Client* client = new Client(protocol);
    endpoint = client;
    client->init("", client_path);
    client->handshake();
    std::cout << "Received id: " << client->getId() << "\n";
    return 0;
}

/**
 * Send data to specified client
 *
 * \param data pointer to the buffer with data
 * \param count number of entities to send
 * \param data_type type of data to send
 * \param destination id of the client to receive data
 */
void MCL_send(void *data, int count, int data_type, int destination) {
    DataType type = static_cast<DataType>(data_type);
    endpoint->sendRaw(data, count, destination, type);
}

/**
 * Receive data from a specified client
 *
 * \param buffer buffer to store data
 * \param count number of entities to receive
 * \param data_type type of data to send
 * \param source id of the client which is sending data
 */
void MCL_receive(void *buffer, int count, int data_type, int source) {
    DataType type = static_cast<DataType>(data_type);
    endpoint->requestRaw(buffer, count, source, type);
}

/**
 * Destroy the endpoint
 */
void MCL_destroy() {
    endpoint->destroy();
}


#endif //MIMICCOMMLIB_MESSAGESERVICE_H
