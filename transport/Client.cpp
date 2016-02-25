//
// Created by bolnykh on 24.02.16.
//

#include "Client.h"

int Client::init(char *address, Transport protocol) {
    protocol.initClient();
}


int Client::send(Message *msg, char *destination) {
    protocol.connectAddress(destination);
    protocol.sendMessage(msg, destination);
}

Message Client::request(char *source) {
    protocol.connectAddress(source);
    Message* request = new Message();
    protocol.sendMessage(request, source);
    Message response = protocol.receiveMessage(source);
    return response;
}

