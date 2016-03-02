//
// Created by bolnykh on 24.02.16.
//

#ifndef MIMICCOMMLIB_CLIENT_H
#define MIMICCOMMLIB_CLIENT_H


#include "../message/Message.h"
#include "Endpoint.h"

class Client : public Endpoint {

public:
    Client(Transport* protocol) : Endpoint(protocol) { }

    virtual void handshake() override;

    virtual int init(char *address, Transport protocol);

    virtual int connect(int dest);

    virtual int send(Message *msg, int destination);

    virtual Message * request(int source);

    virtual void disconnect(int dest);

    virtual void destroy();

private:
    char* serverAddress;
};


#endif //MIMICCOMMLIB_CLIENT_H
