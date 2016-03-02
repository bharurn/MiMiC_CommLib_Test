//
// Created by bolnykh on 24.02.16.
//

#include "Server.h"
#include "../message/ClientData.h"
#include <cstring>

int Server::init(char *address, Transport protocol, const int clientsNumber, char** clientPaths) {
    Server::protocol->initServ();
    Server::clientsNumber = clientsNumber;
    for (int i = 0; i < clientsNumber; ++i) {
        Endpoint client = Endpoint(Server::protocol);
        client.setId(i + 1);
        client.setPath(clientPaths[i]);
        client_list.push_back(client);
    }
}

int Server::connect(int dest) {

}

int Server::send(Message *msg, int destination) {
    for (Endpoint &eachClient : client_list) {
        if (eachClient.getId() == destination) {
            protocol->acceptConnection(eachClient.getAddress());
            protocol->receiveMessage(eachClient.getAddress());
            protocol->sendMessage(msg, eachClient.getAddress());
            disconnect(destination);
        }
    }
}

Message * Server::request(int source) {
    for (Endpoint &eachClient : client_list) {
        if (eachClient.getId() == source) {
            protocol->acceptConnection(eachClient.getAddress());
            Message* msg = protocol->receiveMessage(eachClient.getAddress());
            disconnect(source);
            return msg;
        }
    }
    return new Message();
}

void Server::disconnect(int dest) {
    protocol->closeConnection();
}

void Server::destroy() {
    protocol->closeConnection();
}

int Server::broadcast(Message *msg) {
    for (Endpoint &eachClient : client_list) {
        send(msg, eachClient.getId());
    }
    return 0;
}

void Server::handshake() {
    for (int i = 0; i < clientsNumber; ++i) {
        protocol->acceptConnection(protocol->getServerAddress());
        Message* clientMsg = protocol->receiveMessage(protocol->getServerAddress());
        ClientData* data = (ClientData*) clientMsg->data;
        for(Endpoint &eachClient : client_list) {
            if (std::strcmp(eachClient.getPath(), data->clientPath.c_str()) == 0) {
                eachClient.setAddress(data->clientAddress.c_str());
                data->clientId = eachClient.getId();
                protocol->sendMessage(clientMsg, eachClient.getAddress());
                protocol->closeConnection();
                break;
            }
        }
    }
}
