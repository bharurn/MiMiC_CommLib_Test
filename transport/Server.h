//
// Created by bolnykh on 24.02.16.
//

#ifndef MIMICCOMMLIB_SERVER_H
#define MIMICCOMMLIB_SERVER_H


#include "Endpoint.h"
#include "Client.h"

class Server : public Endpoint {

private:
    int clientsNumber;

public:
    Server(Transport *protocol, char* address) : Endpoint(protocol) { }

    virtual int init(char *address, Transport protocol, const int clientsNumber, char** clientPaths);

    virtual int connect(int dest);

    virtual int send(Message *msg, int destination);

    int broadcast(Message *msg);

    virtual Message * request(int source);

    virtual void disconnect(int dest);

    virtual void destroy();

    virtual void message_handshake();

    virtual void handshake();


    virtual int sendRaw(void *data, int count, int destination, DataType type);

    virtual RawDataStruct *requestRaw(int source, DataType type);

    void setCleints_number(int cleints_number) {
        Server::clientsNumber = cleints_number;
    }
};


#endif //MIMICCOMMLIB_SERVER_H
