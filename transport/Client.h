//
// Created by bolnykh on 24.02.16.
//

#ifndef MIMICCOMMLIB_CLIENT_H
#define MIMICCOMMLIB_CLIENT_H


#include "../message/Message.h"
#include "Endpoint.h"

/**
 * Endpoint representing a client (slave) side
 */
class Client : public Endpoint {

public:
    Client(Transport* protocol) : Endpoint(protocol) { }

    Client(int id, const std::string &path, Transport *protocol) : Endpoint(id, path, protocol) { }

    int send(void *data, int count, int destination, DataType type);

    void request(void *data, int count, int source, DataType type);

    void handshake();

    int init(std::string address, std::string path);

    void disconnect(int dest);

    void destroy();

private:
    /**
     * Ugly, just ugly - but could be useful if at certain point we create a p2p
     * solution
     */
    static const int clientsNumber = 1;

};


#endif //MIMICCOMMLIB_CLIENT_H
