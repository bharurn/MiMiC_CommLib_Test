//
// Created by bolnykh on 23.02.16.
//

#ifndef MIMICCOMMLIB_ENDPOINT_H
#define MIMICCOMMLIB_ENDPOINT_H


#include <iostream>
#include "Transport.h"
#include "../DataTypes.h"

/**
 * Endpoint class representing clients involved in data communications
 */
class Endpoint {

protected:

    /**
     * Transport protocol used to send data
     */
    Transport* protocol;

    /**
     * List of known client (needed for server, but could be useful for p2p transports
     */
    std::vector<Endpoint*> client_list;

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

public:

    Endpoint(Transport *protocol) : protocol(protocol) { }


    Endpoint(int id, const std::string &path, Transport *protocol) :
            id(id), path(path), protocol(protocol) { }

    /**
     * Initialize endpoint
     *
     * \param paths paths to other endpoints which this one is
     * interacting with.
     */
    virtual int init(std::vector<std::string> paths) = 0;

    /**
     * Handshake procedure, assigns ids to clients
     */
    virtual void handshake() {}

    /**
     * Send data to a specific client (transport layer should handle data packaging)
     *
     * \param data pointer to the data array
     * \param count number of data entities
     * \param destination id of the client to receive data
     * \param type of the data to send
     */
    virtual int send(void *data, int count, int destination, DataType type) = 0;

    /**
     * Receive raw data (array of primitive type) from a specific client
     *
     * \param data pointer to the buffer
     * \param count number of data entities
     * \param source id of the client to receive data
     * \param type of the data to send
     */
    virtual void request(void *data, int count, int source, DataType type) = 0;

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
    virtual void disconnect(int dest) = 0;

    /**
     * Destroy the endpoint
     */
    virtual void destroy () {}

    std::string transform_path(std::string original_path) {
        char sep = '/';
        std::string transformed_path = std::string(original_path);
        if (original_path[original_path.length() - 1] != sep) {
            transformed_path += sep;
        }
        return transformed_path;
    }

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
