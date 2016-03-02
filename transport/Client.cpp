//
// Created by bolnykh on 24.02.16.
//

#include "Client.h"
#include "../message/ClientData.h"

int Client::init(char *address, Transport protocol) {
    Client::protocol->initClient();
    Endpoint server = Endpoint(Client::protocol);
    server.setId(0);
    server.setAddress(protocol.getServerAddress());
    client_list.push_back(server);
}


int Client::send(Message *msg, int destination) {
    for (Endpoint &eachPoint : client_list) {
        if (eachPoint.getId() == destination) {
            protocol->connectAddress(eachPoint.getAddress());
            protocol->sendMessage(msg, eachPoint.getAddress());
        }
    }
    // TODO: normal response codes
    return 0;
}

Message * Client::request(int source) {
    Message* response = nullptr;
    for (Endpoint &eachPoint : client_list) {
        if (eachPoint.getId() == source) {
            protocol->connectAddress(eachPoint.getAddress());
            Message* request = new Message();
            protocol->sendMessage(request, eachPoint.getAddress());
            response = protocol->receiveMessage(eachPoint.getAddress());
        }
    }
    // TODO: response handle
    return response;
}

int Client::connect(int dest) {
    for (Endpoint &eachPoint : client_list) {
        if (eachPoint.getId() == dest) {
            protocol->connectAddress(eachPoint.getAddress());
        }
    }
    return 0;
}

void Client::disconnect(int dest) {

}

void Client::destroy() {

}

void Client::handshake() {
    Message* clientDataRequest = new Message();
    ClientData* data = new ClientData();
    data->clientPath = Client::getPath();
    data->clientAddress = Client::getAddress();
    clientDataRequest->data = data;
    char* serverAddress = protocol->getServerAddress();
    protocol->connectAddress(serverAddress);
    protocol->sendMessage(clientDataRequest, serverAddress);
    Message* msg = protocol->receiveMessage(serverAddress);
    ClientData* updatedData = (ClientData*) msg->data;
    Client::setId(updatedData->clientId);
}
