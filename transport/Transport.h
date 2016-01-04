//
// Created by bolnykh on 12/7/15.
//

#include <zconf.h>
#include "../message/Message.h"
#include "../serializer/Serializer.h"
#include <map>

#ifndef MIMICCOMMLIB_TRANSPORT_H
#define MIMICCOMMLIB_TRANSPORT_H

/**
 * Abstract class of transport layer
 */
class  Transport {

protected:
    /*
     * Serializer used for serialization/deserialization of messages
     */
    Serializer *serializer;

public:
    Transport(Serializer *serializer) : serializer(serializer) { }

    /**
     * Initialize server for receiving/sending data
     *
     * \param clients_number number of clients to get data from
     * \param replies map of client_id -> reply from the server
     */
    virtual void initServ(int clients_number, std::map<int, Message*> replies) {}

    /**
     * Initialize client (prepare and connect to the server) for data interaction
     */
    virtual void initClient() {}

    /**
     * Send a message to a server
     *
     * \param msg message to send
     */
    virtual void sendMessage(Message *msg) {}

    void setSerializer(Serializer *serializer) {
        Transport::serializer = serializer;
    }

};
#endif //MIMICCOMMLIB_TRANSPORT_H