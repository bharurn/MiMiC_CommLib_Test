//
// Created by bolnykh on 24.02.16.
//

#include "Client.h"
#include "../message/ClientData.h"
#include "MPITransport.h"

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

void Client::message_handshake() {
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

void Client::handshake() {
    MPITransport* transport = (MPITransport*) protocol;
    char* serverAddress = transport->getServerAddress();
    transport->connectAddress(serverAddress);
    transport->sendRawData(getAddress(), MPI_CHARACTER, getAddress_size(), MPI_ANY_TAG, 1);
    int* id = (int *) transport->receiveRawData(MPI_INT, 0)->data;
    transport->closeConnection();
    Client::setId(id[0]);
}

int Client::sendRaw(void *data, int count, int destination, DataType type) {
    MPITransport* transport = (MPITransport*) protocol;
    MPI_Datatype send_type = transport->pick_mpi_type(type);

    for (Endpoint &eachPoint : client_list) {
        if (eachPoint.getId() == destination) {
            transport->connectAddress(eachPoint.getAddress());
            transport->sendRawData(data, send_type, count, destination, getId());
            transport->closeConnection();
            break;
        }
    }
    return 0;
}

RawDataStruct *Client::requestRaw(int source, DataType type) {
    MPITransport* transport = (MPITransport*) protocol;
    MPI_Datatype receiveType = transport->pick_mpi_type(type);
    RawDataStruct* received = nullptr;
    for (Endpoint &eachPoint : client_list) {
        if (eachPoint.getId() == source) {
            transport->connectAddress(eachPoint.getAddress());
            received = transport->receiveRawData(receiveType, source);
            transport->closeConnection();
            break;
        }
    }
    return received;
}
