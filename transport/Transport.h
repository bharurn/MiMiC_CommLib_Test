//
// Created by bolnykh on 12/7/15.
//

#include <zconf.h>
#include "../message/Message.h"
#include "../serializer/Serializer.h"
#include <map>
#include "Endpoint.h"


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
    virtual void initServ() {}

    /**
     * Initialize client (prepare and connect to the server) for data interaction
     */
    virtual void initClient() {}

    /**
     * Send a message to a server
     *
     * \param msg message to send
     */
    virtual void sendMessage(Message *msg, char* destination) {}

    virtual Message receiveMessage(char* source) {}

    virtual int connectAddress (char* address) {}

    virtual void closeConnection () {}

    void setSerializer(Serializer *serializer) {
        Transport::serializer = serializer;
    }

};