//
// Created by bolnykh on 23.02.16.
//

#ifndef MIMICCOMMLIB_ENDPOINT_H
#define MIMICCOMMLIB_ENDPOINT_H


#include "Transport.h"

class Endpoint {
    int id;
    char* address;

protected:
    Transport* protocol;
public:

    Endpoint(Transport *protocol) : protocol(protocol) { }

    virtual int init(char* address, Transport protocol) {}

    virtual int connect (char* dest) {}

    virtual int send(Message *msg, char *destination) {}

    virtual Message request(char* source) {}

    virtual void disconnect (char* dest) {}

    virtual void destroy () {}


    int getId() const {
        return id;
    }

    char *getAddress() const {
        return address;
    }
};


#endif //MIMICCOMMLIB_ENDPOINT_H
