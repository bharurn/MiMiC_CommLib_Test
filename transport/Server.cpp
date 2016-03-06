//
// Created by bolnykh on 24.02.16.
//

#include "Server.h"
#include "../message/ClientData.h"
#include "MPITransport.h"
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

void Server::message_handshake() {
    for (int i = 0; i < clientsNumber; ++i) {
        protocol->acceptConnection(protocol->getServerAddress());
        Message* clientMsg = protocol->receiveMessage(protocol->getServerAddress());
        ClientData* data = (ClientData*) clientMsg->data;
        for(Endpoint &eachClient : client_list) {
            if (std::strcmp(eachClient.getPath(), data->clientPath.c_str()) == 0) {
                eachClient.setAddress((char *) data->clientAddress.c_str());
                data->clientId = eachClient.getId();
                protocol->sendMessage(clientMsg, eachClient.getAddress());
                protocol->closeConnection();
                break;
            }
        }
    }
}

void Server::handshake() {
    MPITransport* transport = (MPITransport*) protocol;
    for (int i = 0; i < clientsNumber; ++i) {
        transport->acceptConnection(transport->getServerAddress());
        char* client_path = (char*) transport->receiveRawData(MPI_CHARACTER, MPI_ANY_TAG)->data;
        std::cout << client_path << " \n";
        for(Endpoint &eachClient : client_list) {
            if (std::strcmp(eachClient.getPath(), client_path) == 0) {
                int id = eachClient.getId();
                std::cout << "send\n";
                transport->sendRawData(&id, MPI_INT, 1, MPI_ANY_TAG, 0);
                std::cout << "disconnect\n";
                transport->closeConnection();
                std::cout << "disconnected\n";
                break;
            }
        }
    }
}

int Server::sendRaw(void *data, int count, int destination, DataType type) {
    MPITransport* transport = (MPITransport*) protocol;
    MPI_Datatype send_type = transport->pick_mpi_type(type);

    for (Endpoint &eachPoint : client_list) {
        if (eachPoint.getId() == destination) {
            transport->acceptConnection(eachPoint.getAddress());
            transport->sendRawData(data, send_type, count, destination, 0);
            transport->closeConnection();
            break;
        }
    }
    return 0;
}

RawDataStruct *Server::requestRaw(int source, DataType type) {
    MPITransport* transport = (MPITransport*) protocol;
    MPI_Datatype receiveType = transport->pick_mpi_type(type);
    RawDataStruct* received = nullptr;
    for (Endpoint &eachPoint : client_list) {
        if (eachPoint.getId() == source) {
            transport->acceptConnection(eachPoint.getAddress());
            received = transport->receiveRawData(receiveType, source);
            transport->closeConnection();
            break;
        }
    }
    return received;
}
