//
// Created by bolnykh on 24.02.16.
//

#ifndef MIMICCOMMLIB_SERVER_H
#define MIMICCOMMLIB_SERVER_H


#include "Endpoint.h"
#include "Client.h"

class Server : public Endpoint {

private:
    int cleints_number;
    std::map<Client> knownClients;

public:
    Server(const Transport &protocol, const int clientsNumber) : Endpoint(protocol) { }

    virtual int init(char *address, Transport protocol);

    virtual int connect(char *dest);

    virtual int send(Message *msg, char *destination);

    int broadcast(Message *msg);

    virtual Message request(char *source);

    virtual void disconnect(char *dest);

    virtual void destroy();
};


#endif //MIMICCOMMLIB_SERVER_H
