//
// Created by bolnykh on 12/7/15.
//
#ifndef MIMICCOMMLIB_TRANSPORT_H
#define MIMICCOMMLIB_TRANSPORT_H

#include <zconf.h>
#include "../message/Message.h"
#include "../serializer/Serializer.h"
#include <map>



/**
 * Abstract class of transport layer
 */
class Transport {

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
    virtual void sendMessage(Message *msg, std::string destination) {}

    virtual Message* receiveMessage(std::string source) {}

    virtual Message* receiveMessages(int number, std::string adresses) {}

    virtual int connectAddress (std::string address) {}

    virtual int acceptConnection(std::string address) {}

    virtual void closeConnection () {}

    virtual char* getServerAddress () {}

    void setSerializer(Serializer *serializer) {
        Transport::serializer = serializer;
    }

};

#endif //MIMICCOMMLIB_TRANSPORT_H