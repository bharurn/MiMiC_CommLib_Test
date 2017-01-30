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

    Server(int id, const std::string &path, Transport *protocol) : Endpoint(id, path, protocol) { }

    int init(std::vector<std::string> paths);

    void disconnect(int dest);

    void destroy();

    void handshake();

    int send(void *data, int count, int destination, DataType type);

    void request(void *data, int count, int source, DataType type);

    void set_clients_number(int clients_number) {
        Server::clientsNumber = clients_number;
    }
};


#endif //MIMICCOMMLIB_SERVER_H
