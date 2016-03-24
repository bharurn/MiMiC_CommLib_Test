//
// Created by bolnykh on 24.02.16.
//

#include "Client.h"
#include "../message/ClientData.h"
#include "MPITransport.h"

int Client::init(std::string address, std::string path) {
    protocol->initClient(transform_path(path));
    Endpoint server = Endpoint(protocol);
    server.setId(0);
    server.setAddress(protocol->getServerAddress());
    client_list.push_back(server);
    setAddress(address);
    setPath(transform_path(path));
}


int Client::send(Message *msg, int destination) {
    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachPoint = client_list[i];
        if (eachPoint.getId() == destination) {
            protocol->connectAddress(destination);
            protocol->sendMessage(msg, eachPoint.getAddress());
        }
    }
    // TODO: normal response codes
    return 0;
}

Message * Client::request(int source) {
    Message* response = NULL;
    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachPoint = client_list[i];
        if (eachPoint.getId() == source) {
            protocol->connectAddress(source);
            Message* request = new Message();
            protocol->sendMessage(request, eachPoint.getAddress());
            response = protocol->receiveMessage(eachPoint.getAddress());
        }
    }
    // TODO: response handle
    return response;
}

int Client::connect(int dest) {
    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachPoint = client_list[i];
        if (eachPoint.getId() == dest) {
            protocol->connectAddress(dest);
        }
    }
    return 0;
}

void Client::disconnect(int dest) {
    protocol->closeConnection(dest);
}

void Client::destroy() {
    disconnect(0);
}

void Client::message_handshake() {
    Message* clientDataRequest = new Message();
    ClientData* data = new ClientData();
    data->clientPath = Client::getPath();
    data->clientAddress = Client::getAddress();
    clientDataRequest->data = data;

    char* serverAddress = protocol->getServerAddress();
    protocol->connectAddress(0);
    protocol->sendMessage(clientDataRequest, serverAddress);
    Message* msg = protocol->receiveMessage(serverAddress);
    ClientData* updatedData = (ClientData*) msg->data;
    Client::setId(updatedData->clientId);
}

void Client::handshake() {
    MPITransport* transport = (MPITransport*) protocol;
    transport->connectAddress(0);
    transport->sendRawData((char *) getPath().c_str(), TYPE_CHAR, getPath().length(), 0, 1);

    int id;
    transport->receiveRawData(&id, TYPE_INT, 1, 0);
    Client::setId(id);
}

int Client::sendRaw(void *data, int count, int destination, DataType type) {
    MPITransport* transport = (MPITransport*) protocol;

    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachPoint = client_list[i];
        if (eachPoint.getId() == destination) {
            transport->sendRawData(data, type, count, destination, getId());
            break;
        }
    }
    return 0;
}

void Client::requestRaw(void* data, int count, int source, DataType type) {
    MPITransport* transport = (MPITransport*) protocol;
    for (int i = 0; i < clientsNumber; i++) {
        Endpoint eachPoint = client_list[i];
        if (eachPoint.getId() == source) {
            transport->receiveRawData(data, type, count, source);
            break;
        }
    }
}
