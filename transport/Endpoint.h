//
// Created by bolnykh on 23.02.16.
//

#ifndef MIMICCOMMLIB_ENDPOINT_H
#define MIMICCOMMLIB_ENDPOINT_H


#include "Transport.h"
#include "../DataTypes.h"
#include "../message/RawDataStruct.h"

class Endpoint {
    int id, address_size, path_size;
    char* address;
    char* path;

protected:
    Transport* protocol;
    std::vector <Endpoint> client_list;
public:

    Endpoint(Transport *protocol) : protocol(protocol) { }

    virtual int init(char* address, Transport protocol) {}

    virtual void message_handshake() {}

    virtual void handshake() {}

    virtual void initClientList(Endpoint clients[]) {};

    virtual int connect(int dest) {}

    virtual int send(Message *msg, int destination) {}

    virtual Message * request(int source) {}

    virtual int sendRaw(void* data, int count, int destination, DataType type) {}

    virtual RawDataStruct* requestRaw (int source, DataType type) {}

    virtual void disconnect(int dest) {}

    virtual void destroy () {}

    int getId() {
        return id;
    }

    char *getAddress() {
        return address;
    }


    char *getPath() {
        return path;
    }

    void setId(int id) {
        Endpoint::id = id;
    }

    void setAddress(char *address) {
        Endpoint::address = address;
    }

    void setPath(char *path) {
        Endpoint::path = path;
    }


    int getAddress_size() {
        return address_size;
    }

    int getPath_size() {
        return path_size;
    }


    void setAddress_size(int address_size) {
        Endpoint::address_size = address_size;
    }

    void setPath_size(int path_size) {
        Endpoint::path_size = path_size;
    }
};


#endif //MIMICCOMMLIB_ENDPOINT_H
