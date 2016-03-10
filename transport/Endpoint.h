//
// Created by bolnykh on 23.02.16.
//

#ifndef MIMICCOMMLIB_ENDPOINT_H
#define MIMICCOMMLIB_ENDPOINT_H


#include "Transport.h"
#include "../DataTypes.h"

/**
 * Endpoint class representing clients involved in data communications
 */
class Endpoint {

    /**
     * Endpoint id
     */
    int id;

    /**
     * Network address of the endpoint
     */
    std::string address;

    /**
     * Local path associated with the current endpoint
     */
    std::string path;

protected:

    /**
     * Transport protocol used to send data
     */
    Transport* protocol;

    /**
     * List of known client (needed for server, but could be useful for p2p transports
     */
    std::vector <Endpoint> client_list;

public:

    Endpoint(Transport *protocol) : protocol(protocol) { }

    /**
     * Initialize endpoint (overloaded for client and server)
     */
    virtual int init(std::string *address, std::string *path) {}

    /**
     * Handshake procedure for a transport without messaging system
     */
    virtual void message_handshake() {}

    /**
     * Handshake procedure for transports with internal messaging
     * mechinsms (MPI, PAMI, etc.)
     */
    virtual void handshake() {}

    /**
     * @Deprecated
     */
    virtual void initClientList(Endpoint clients[]) {};

    /**
     * @Deprecated?
     */
    virtual int connect(int dest) {}

    /**
     * Send a message to specified client
     *
     * \param msg message to send
     * \param destination id of the client to receive data
     */
    virtual int send(Message *msg, int destination) {}

    /**
     * Request a message from a client
     *
     * \param source id of the source client
     */
    virtual Message * request(int source) {}

    /**
     * Send raw data (array of primitive type) to a specific client
     * !!!ONLY FOR MESSAGE_BASED MECHANISMS(MPI, PAMI)  !!!
     * !!!FOR SIMPLER MECHANISMS MESSAGES SHOULD BE USED!!!
     *
     * \param data pointer to the data array
     * \param count number of data entities
     * \param destination id of the client to receive data
     * \param type of the data to send
     */
    virtual int sendRaw(void* data, int count, int destination, DataType type) {}

    /**
     * Receive raw data (array of primitive type) from a specific client
     * !!!ONLY FOR MESSAGE_BASED MECHANISMS(MPI, PAMI)  !!!
     * !!!FOR SIMPLER MECHANISMS MESSAGES SHOULD BE USED!!!
     *
     * \param data pointer to the buffer
     * \param count number of data entities
     * \param source id of the client to receive data
     * \param type of the data to send
     */
    virtual void requestRaw (void* data, int count, int source, DataType type) {}

    /**
     * Probe message queue for length of the pending message
     *
     * \param client id of the client
     * \param type of the data to check
     */
    int probe(int client, DataType type) {
        return protocol->probe(client, type);
    }

    /**
     * Disconnect from a specified client
     */
    virtual void disconnect(int dest) {}

    /**
     * Destroy the endpoint
     */
    virtual void destroy () {}

    int getId() {
        return id;
    }

    std::string getAddress() {
        return address;
    }


    std::string getPath() {
        return path;
    }

    void setId(int id) {
        Endpoint::id = id;
    }

    void setAddress(std::string address) {
        Endpoint::address = address;
    }

    void setPath(std::string path) {
        Endpoint::path = path;
    }
};


#endif //MIMICCOMMLIB_ENDPOINT_H
