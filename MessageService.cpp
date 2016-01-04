//
// Created by bolnykh on 12/7/15.
//

#include "MessageService.h"

void MessageService::sendMessage(Message message) {
    transport.initClient();
    transport.sendMessage(&message);
}

void MessageService::initServer(int clients_number, std::map<int, Message*> replies) {
    transport.initServ(clients_number, replies);
}
