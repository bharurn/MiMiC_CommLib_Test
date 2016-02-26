//
// Created by bolnykh on 24.02.16.
//

#include "Server.h"

int Server::init(char *address, Transport protocol) {
    protocol.initServ();
}

int Server::connect(char *dest) {

}

int Server::send(Message *msg, char *destination) {
    protocol->receiveMessage(destination);
    protocol->sendMessage(msg, destination);
    disconnect(destination);
}

Message Server::request(char *source) {
    Message msg = protocol->receiveMessage(source);
    disconnect(source);
    return msg;
}

void Server::disconnect(char *dest) {
    protocol->closeConnection();
}

void Server::destroy() {
    Endpoint::destroy();
}

int Server::broadcast(Message *msg) {

    return 0;
}
