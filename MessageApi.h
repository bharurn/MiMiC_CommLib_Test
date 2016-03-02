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

Endpoint* endpoint;

int initServer() {
    Transport* protocol = new BoostSocketTransport(new BoostSerializer, "./demo_socket");
    Server* server = new Server(protocol, "./demo_socket");
}


#endif //MIMICCOMMLIB_MESSAGESERVICE_H
