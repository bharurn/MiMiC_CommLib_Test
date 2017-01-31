//
// Created by bolnykh on 24.02.16.
//

#include "Client.h"
#include "MPITransport.h"
#include "Server.h"

int Client::init(std::vector<std::string> paths) {
    protocol->initClient(transform_path(paths[0]));
    client_list.push_back(new Server(0, "", protocol));
    setPath(transform_path(paths[0]));

    return 0;
}

void Client::disconnect(int dest) {
    protocol->closeConnection(dest);
}

void Client::destroy() {
    disconnect(0);
}

void Client::handshake() {
    protocol->connectAddress(0);
    protocol->sendData((char *) getPath().c_str(), TYPE_CHAR, getPath().length(), 0);

    int id;
    protocol->receiveData(&id, TYPE_INT, 1, 0);
    this->setId(id);
}

int Client::send(void *data, int count, int destination, DataType type) {
    for (int i = 0; i < clientsNumber; i++) {
        if (client_list[i]->getId() == destination) {
            protocol->sendData(data, type, count, destination);
            break;
        }
    }
    return 0;
}

void Client::request(void *data, int count, int source, DataType type) {
    for (int i = 0; i < clientsNumber; i++) {
        if (client_list[i]->getId() == source) {
            protocol->receiveData(data, type, count, source);
            break;
        }
    }
}
