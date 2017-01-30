//
// Created by bolnykh on 12/7/15.
//
#ifndef MIMICCOMMLIB_TRANSPORT_H
#define MIMICCOMMLIB_TRANSPORT_H

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
    virtual void initServ(std::vector<std::string> paths) = 0;

    /**
     * Initialize client (prepare and connect to the server) for data interaction
     */
    virtual void initClient(std::string path) = 0;

    /**
     * Establish connection to a specified address
     */
    virtual int connectAddress (int id) = 0;

    /**
     * Accept a connection on a specified address
     */
    virtual int acceptConnection(int id) = 0;

    /**
     * Disconnect client
     *
     * \param id id of the client to disconnect
     */
    virtual void closeConnection (int id) = 0;

    /**
     * Returns the address of the local server (remove?)
     */
    virtual char* getServerAddress () = 0;

    /**
     * Analogue to MPI_Probe return the size of the message waiting in the queue
     *
     * \param id id of the client
     * \param type DataType to be received
     */
    virtual int probe(int id, DataType type) = 0;

    /**
     * Destroy the port associated with the specified path
     */
    virtual void destroy(std::string path) = 0;

    virtual void sendData(void *data, DataType type, int count, int id) = 0;

    virtual void receiveData(void *data_holder, DataType type, int count, int id) = 0;

    void setSerializer(Serializer *serializer) {
        Transport::serializer = serializer;
    }

};

#endif //MIMICCOMMLIB_TRANSPORT_H