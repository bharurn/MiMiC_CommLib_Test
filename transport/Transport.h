//
// Created by bolnykh on 12/7/15.
//
#ifndef MIMICCOMMLIB_TRANSPORT_H
#define MIMICCOMMLIB_TRANSPORT_H

#include <zconf.h>
#include "../message/Message.h"
#include "../serializer/Serializer.h"
#include "../DataTypes.h"



/**
 * Abstract class of transport layer
 *
 * TODO: Consider dividing into two abstract classes: MessageBasedTransport and Plain
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
    virtual void initServ(std::string *paths, int client_number) {}

    /**
     * Initialize client (prepare and connect to the server) for data interaction
     */
    virtual void initClient(std::string path) {}

    /**
     * Used to bind a network address to specific client (most possibly has to be removed)
     */
    virtual void bindAddress(std::string path) {}

    /**
     * Send a message to a specified address
     *
     * \param msg message to send
     * \param destination address of the client to obtain the message
     */
    virtual void sendMessage(Message *msg, std::string destination) {}

    /**
     * Receive a message from a specified source
     *
     * \param source address of the client sending the message
     */
    virtual Message* receiveMessage(std::string source) {}

    /**
     * Deprecate?
     */
    virtual Message* receiveMessages(int number, std::string adresses) {}

    /**
     * Establish connection to a specified address
     */
    virtual int connectAddress (int id) {}

    /**
     * Accept a connection on a specified address
     */
    virtual int acceptConnection(int id) {}

    /**
     * Disconnect client
     *
     * \param id id of the client to disconnect
     */
    virtual void closeConnection (int id) {}

    /**
     * Returns the address of the local server (remove?)
     */
    virtual char* getServerAddress () {}

    /**
     * Analogue to MPI_Probe return the size of the message waiting in the queue
     *
     * \param id id of the client
     * \param type DataType to be received
     */
    virtual int probe(int id, DataType type) {}

    /**
     * Destroy the port associated with the specified path
     */
    virtual void destroy(std::string path) {}

    virtual void sendRawData(void *data, DataType type, int number, int id, int endpoint_id) {}

    virtual void receiveRawData(void * data_holder, DataType type, int count, int id) {}

    void setSerializer(Serializer *serializer) {
        Transport::serializer = serializer;
    }

};

#endif //MIMICCOMMLIB_TRANSPORT_H