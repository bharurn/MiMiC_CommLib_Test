//
// Created by bolnykh on 12/14/15.
//

#ifndef MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H
#define MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H


#include <boost/asio/local/stream_protocol.hpp>
#include "Transport.h"

/**
 * Transport implementation using boost socket library to work with UNIX sockets
 */
class BoostSocketTransport : public Transport {

public:
    BoostSocketTransport(Serializer *serializer) : Transport(serializer) { }

    /**
     * Size of the buffer to be initialized for data transfer
     */
    const static long BUFFER_SIZE = 1 * 1024 * 1024;

private:
    virtual void initServ(int clients_number, const char* file, std::map<int, Message*> replies) override;

    virtual void initClient() override;

    virtual void sendMessage(Message *msg) override;

    /**
     * Internal routine used for sending messages through a socket
     */
    void sendMessageInternal(Message* msg, boost::asio::local::stream_protocol::socket* socket);

    /**
     * Internal function to read raw data from the socket
     */
    char* readData(boost::asio::local::stream_protocol::socket* socket_);

};


#endif //MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H
