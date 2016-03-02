//
// Created by bolnykh on 23.02.16.
//

#ifndef MIMICCOMMLIB_ENDPOINT_H
#define MIMICCOMMLIB_ENDPOINT_H


#include "Transport.h"

class Endpoint {
    int id;
    const char* address;
    char* path;

protected:
    Transport* protocol;
    std::vector <Endpoint> client_list;
public:

    Endpoint(Transport *protocol) : protocol(protocol) { }

    virtual int init(char* address, Transport protocol) {}

    virtual void handshake() {}

    virtual void initClientList(Endpoint clients[]) {};

    virtual int connect(int dest) {}

    virtual int send(Message *msg, int destination) {}

    virtual Message * request(int source) {}

    virtual void disconnect(int dest) {}

    virtual void destroy () {}

    int getId() const {
        return id;
    }

    const char *getAddress() const {
        return address;
    }


    char *getPath() const {
        return path;
    }

    void setId(int id) {
        Endpoint::id = id;
    }

    void setAddress(const char *address) {
        Endpoint::address = address;
    }

    void setPath(char *path) {
        Endpoint::path = path;
    }
};


#endif //MIMICCOMMLIB_ENDPOINT_H
