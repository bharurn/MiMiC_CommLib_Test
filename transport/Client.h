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

    void message_handshake();

    int sendRaw(void *data, int count, int destination, DataType type);

    void requestRaw(void* data, int count, int source, DataType type);

    void handshake() ;

    int init(std::string address, std::string path);

    int connect(int dest);

    int send(Message *msg, int destination);

    Message * request(int source);

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
