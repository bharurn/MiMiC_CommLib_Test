//
// Created by bolnykh on 12/7/15.
//

#ifndef MIMICCOMMLIB_MESSAGESERVICE_H
#define MIMICCOMMLIB_MESSAGESERVICE_H


#include "transport/Transport.h"
#include "transport/BoostSocketTransport.h"
#include "serializer/BoostSerializer.h"
#include "transport/Client.h"
#include "transport/Server.h"

/**
 * Singleton class representing messaging service used by the library (should be initialized)
 */
class MessageService {

private:
    Endpoint* ep = NULL;

public:
    MessageService() { }

    void init(char* address) {
        ep = new Client(new BoostSocketTransport(new BoostSerializer(), address));
        ep->init(address, NULL);
    }

    void init(char* address, int clients_number) {
        ep = new Server(new BoostSocketTransport(new BoostSerializer(), address), address, clients_number);
        ep->init(address, NULL);
    }


    void sendMessage(Message message, char* address) {

    }

};


#endif //MIMICCOMMLIB_MESSAGESERVICE_H
