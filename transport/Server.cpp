//
// Created by bolnykh on 24.02.16.
//

#include "Server.h"
#include "../message/ClientData.h"
#include "MPITransport.h"
#include <cstring>

int Server::init(const int clientsNumber, std::string *paths) {
    std::string transformed_paths[clientsNumber];
    for (int i = 0; i < clientsNumber; ++i) {
        transformed_paths[i] = transform_path(paths[i]);
    }
    Server::protocol->initServ(transformed_paths, clientsNumber);
    Server::clientsNumber = clientsNumber;

    for (int i = 0; i < clientsNumber; ++i) {
        Endpoint client = Endpoint(Server::protocol);
        client.setId(i + 1);
        client.setPath(transformed_paths[i]);
        client_list.push_back(client);
    }
}

int Server::connect(int dest) {
    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachClient = client_list[i];
        if (eachClient.getId() == dest) {
            protocol->acceptConnection(dest);
        }
    }

    return 0;
}

int Server::send(Message *msg, int destination) {
    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachClient = client_list[i];
        if (eachClient.getId() == destination) {
            protocol->acceptConnection(destination);
            protocol->receiveMessage(eachClient.getAddress());
            protocol->sendMessage(msg, eachClient.getAddress());
            disconnect(destination);
        }
    }

    return 0;
}

Message * Server::request(int source) {
    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachClient = client_list[i];
        if (eachClient.getId() == source) {
            protocol->acceptConnection(source);
            Message* msg = protocol->receiveMessage(eachClient.getAddress());
            disconnect(source);
            return msg;
        }
    }

    return new Message();
}

void Server::disconnect(int dest) {
    protocol->closeConnection(dest);
}

void Server::destroy() {
    for (int i = 0; i < clientsNumber; ++i) {
        protocol->closeConnection(i + 1);
        Endpoint each_client = client_list[i];
        protocol->destroy(each_client.getPath());
    }
}

int Server::broadcast(Message *msg) {
    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachClient = client_list[i];
        send(msg, eachClient.getId());
    }
    return 0;
}

void Server::message_handshake() {
    for (int i = 0; i < clientsNumber; ++i) {
        protocol->acceptConnection(i + 1);
        Message* clientMsg = protocol->receiveMessage(protocol->getServerAddress());
        ClientData* data = (ClientData*) clientMsg->data;

        for (int j = 0; j < clientsNumber; j++) {
            Endpoint eachClient = client_list[j];
            if (std::strcmp(eachClient.getPath().c_str(), data->clientPath.c_str()) == 0) {
                eachClient.setAddress((char *) data->clientAddress.c_str());
                data->clientId = eachClient.getId();
                protocol->sendMessage(clientMsg, eachClient.getAddress());
                protocol->closeConnection(eachClient.getId());
                break;
            }
        }
    }
}

void Server::handshake() {
    MPITransport* transport = (MPITransport*) protocol;
    for (int i = 0; i < clientsNumber; ++i) {
        transport->acceptConnection(i + 1);
        int size = probe(i + 1, TYPE_CHAR);
        char path[size];
        transport->receiveRawData(path, TYPE_CHAR, size, i + 1);
        std::string temp = path;
        temp = temp.substr(0, size);

        for (int j = 0; j < clientsNumber; j++) {
            Endpoint eachClient = client_list[j];
            if (std::strcmp(eachClient.getPath().c_str(), temp.c_str()) == 0) {
                int id = eachClient.getId();
                transport->sendRawData(&id, TYPE_INT, 1, i + 1, 0);
                break;
            }
        }
    }
}

int Server::sendRaw(void *data, int count, int destination, DataType type) {
    MPITransport* transport = (MPITransport*) protocol;

    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachPoint = client_list[i];
        if (eachPoint.getId() == destination) {
            transport->sendRawData(data, type, count, destination, 0);
            break;
        }
    }
    return 0;
}

void Server::requestRaw(void* data, int count, int source, DataType type) {
    MPITransport* transport = (MPITransport*) protocol;

    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachPoint = client_list[i];
        if (eachPoint.getId() == source) {
            transport->receiveRawData(data, type, count, source);
            break;
        }
    }
}
