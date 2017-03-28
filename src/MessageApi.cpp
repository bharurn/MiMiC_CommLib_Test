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
#include <sstream>
#include <iterator>

/**
 * External API of the library
 * NOTE! ALL API CALLS ARE BLOCKING!!!
 */

Endpoint* endpoint;

int MCL_init_server(char *paths_string, char delimeter) {
    std::string merged_paths = std::string(paths_string);
    std::stringstream ss(merged_paths);
    std::string path;
    std::vector<std::string> client_paths;
    while (std::getline(ss, path, delimeter)) {
        if (!path.empty()) {
            client_paths.push_back(path);
        }
    }

    Transport* protocol = new MPITransport(MPI_COMM_SELF);
    Server* server = new Server(protocol);
    server->setId(0);
    endpoint = server;
    server->init(client_paths);
    server->handshake();
    return 0;
}

void MCL_init_client(char *path) {
    std::cout << "start initialization" << "\n";
    Transport* protocol = new MPITransport(MPI_COMM_SELF);
    std::string client_path = std::string(path);
    std::vector<std::string> paths;
    paths.push_back(client_path);
    Client* client = new Client(protocol);
    endpoint = client;
    std::cout << "initializing client" << "\n";
    client->init(paths);
    std::cout << "starting handshake" << "\n";
    client->handshake();
    std::cout << "Received id: " << client->getId() << "\n";
}

void MCL_send(void *data, int count, int data_type, int destination) {
    int temp_type = data_type;
    DataType type = static_cast<DataType>(temp_type);
    endpoint->send(data, count, destination, type);
}

void MCL_receive(void *buffer, int count, int data_type, int source) {
    int temp_type = data_type;
    DataType type = static_cast<DataType>(temp_type);
    endpoint->request(buffer, count, source, type);
}

void MCL_destroy() {
    endpoint->destroy();
}

