//
// Created by bolnykh on 24.02.16.
//

#include "Server.h"
#include "MPITransport.h"
#include <cstring>

int Server::init(std::vector<std::string> paths) {
    int clientsNumber = paths.size();
    std::vector<std::string> transformed_paths;
    for (int i = 0; i < clientsNumber; ++i) {
        transformed_paths.push_back(transform_path(paths[i]));
    }
    this->protocol->initServ(transformed_paths);
    this->clientsNumber = clientsNumber;

    for (int i = 0; i < clientsNumber; ++i) {
        client_list.push_back(new Client(i + 1, transformed_paths[i], protocol));
    }

    return 0;
}

void Server::disconnect(int dest) {
    protocol->closeConnection(dest);
}

void Server::destroy() {
    for (int i = 0; i < clientsNumber; ++i) {
        protocol->closeConnection(i + 1);
        protocol->destroy(client_list[i]->getPath());
    }
}

void Server::handshake() {
    for (int i = 0; i < clientsNumber; ++i) {
        protocol->acceptConnection(i + 1);
        int size = probe(i + 1, TYPE_CHAR);
        char path[size];
        protocol->receiveData(path, TYPE_CHAR, size, i + 1);
        std::string temp = path;
        temp = temp.substr(0, size);

        for (int j = 0; j < clientsNumber; j++) {
            if (std::strcmp(client_list[i]->getPath().c_str(), temp.c_str()) == 0) {
                int id = client_list[i]->getId();
                protocol->sendData(&id, TYPE_INT, 1, i + 1);
                break;
            }
        }
    }
}

int Server::send(void *data, int count, int destination, DataType type) {
    for (int i = 0; i < clientsNumber; i++) {
        if (client_list[i]->getId() == destination) {
            protocol->sendData(data, type, count, destination);
            break;
        }
    }
    return 0;
}

void Server::request(void *data, int count, int source, DataType type) {
    for (int i = 0; i < clientsNumber; i++) {
        if (client_list[i]->getId() == source) {
            protocol->receiveData(data, type, count, source);
            break;
        }
    }
}
