//
// Created by bolnykh on 3/22/16.
//

#include "MessageApi.h"

//
// Created by bolnykh on 12/7/15.
//

#include "transport/Transport.h"
#include "transport/Client.h"
#include "transport/Server.h"
#include "transport/MPITransport.h"

/**
 * External API of the library
 * NOTE! ALL API CALLS ARE BLOCKING!!!
 */

Endpoint* endpoint;

//int MCL_init_server(int clients_number, char *paths_string) {
//    MCL_init_server(clients_number, paths_string, (char *) ";");
//}

/**
 * Use to initialize the server
 *
 * \param clients_number number of clients to be connected
 * \param paths local paths of all clients (needed for addresses sharing)
 */
int MCL_init_server(int *clients_number, char *paths_string, char *delimeter) {
    std::string* client_paths = new std::string[*clients_number];
    char* token;
    token = strtok(paths_string, delimeter);
    int i = 0;
    while (token != NULL && i < *clients_number)
    {
        client_paths[i] = std::string(token);
        token = strtok(NULL, delimeter);
        i++;
    }
    Transport* protocol = new MPITransport(MPI_COMM_SELF);
    Server* server = new Server(protocol);
    server->setId(0);
    endpoint = server;
    server->init(*clients_number, client_paths);
    server->handshake();
    return 0;
}

/**
 * Initialize client endpoint
 *
 * \param path string containing the path in the file system to this client
 */
void MCL_init_client(char *path) {
    std::cout << "start initialization" << "\n";
    Transport* protocol = new MPITransport(MPI_COMM_SELF);
    std::string client_path = std::string(path);
    Client* client = new Client(protocol);
    endpoint = client;
    std::cout << "initializing client" << "\n";
    client->init("", client_path);
    std::cout << "starting handshake" << "\n";
    client->handshake();
    std::cout << "Received id: " << client->getId() << "\n";
}

/**
 * Send data to specified client
 *
 * \param data pointer to the buffer with data
 * \param count number of entities to send
 * \param data_type type of data to send
 * \param destination id of the client to receive data
 */
void MCL_send(void *data, int *count, int *data_type, int *destination) {
    int temp_type = *data_type;
    DataType type = static_cast<DataType>(temp_type);
    endpoint->sendRaw(data, *count, *destination, type);
}

/**
 * Receive data from a specified client
 *
 * \param buffer buffer to store data
 * \param count number of entities to receive
 * \param data_type type of data to send
 * \param source id of the client which is sending data
 */
void MCL_receive(void *buffer, int *count, int *data_type, int *source) {
    int temp_type = *data_type;
    DataType type = static_cast<DataType>(temp_type);
    endpoint->requestRaw(buffer, *count, *source, type);
}

/**
 * Destroy the endpoint
 */
void MCL_destroy() {
    endpoint->destroy();
}

