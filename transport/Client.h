//
// Created by bolnykh on 24.02.16.
//

#ifndef MIMICCOMMLIB_CLIENT_H
#define MIMICCOMMLIB_CLIENT_H


#include "../message/Message.h"
#include "Endpoint.h"

class Client : public Endpoint {

public:
    Client(const Transport &protocol) : Endpoint(protocol) { }


    virtual int init(char *address, Transport protocol);

    virtual int connect(char *dest);

    virtual int send(Message *msg, char *destination);

    virtual Message request(char *source);

    virtual void disconnect(char *dest);

    virtual void destroy();
};


#endif //MIMICCOMMLIB_CLIENT_H
