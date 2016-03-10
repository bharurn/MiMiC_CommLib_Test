//
// Created by bolnykh on 24.02.16.
//

#ifndef MIMICCOMMLIB_SERVER_H
#define MIMICCOMMLIB_SERVER_H


#include "Endpoint.h"
#include "Client.h"

/**
 * Endpoint representing server(master)
 */
class Server : public Endpoint {

private:
    int clientsNumber;

public:
    Server(Transport *protocol) : Endpoint(protocol) { }

    int init(const int clientsNumber, std::string *paths);

    int connect(int dest);

    int send(Message *msg, int destination);

    int broadcast(Message *msg);

    Message * request(int source);

    void disconnect(int dest);

    void destroy();

    void message_handshake();

    void handshake();

    int sendRaw(void *data, int count, int destination, DataType type);

    void requestRaw(void* data, int count, int source, DataType type);

    void setCleints_number(int cleints_number) {
        Server::clientsNumber = cleints_number;
    }
};


#endif //MIMICCOMMLIB_SERVER_H
