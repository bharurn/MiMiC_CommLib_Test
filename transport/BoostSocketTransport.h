//
// Created by bolnykh on 12/14/15.
//

#ifndef MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H
#define MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H


#include <boost/asio/local/stream_protocol.hpp>
#include "Transport.h"
#include "boost/asio/streambuf.hpp"

/**
 * Transport implementation using boost socket library to work with UNIX sockets
 */
class BoostSocketTransport : public Transport {

public:
    BoostSocketTransport(Serializer *serializer, const char *file) : Transport(serializer), file(file) { }
    
    

//    virtual void initServ(int clients_number, std::map<int, Message*> replies);
    void initServ();

    void initClient();

    void sendMessage(Message *msg, std::string destination);

    int acceptConnection(std::string address) override;

    void closeConnection() override;

    Message * receiveMessage(std::string source) override;

    int connectAddress(std::string address) override;

private:
    /**
     * Size of the buffer to be initialized for data transfer
     */
    const static long BUFFER_SIZE = 1 * 1024 * 1024;

    const static int HEADER_SIZE = 16;

    const char* file;

    /**
     * Internal routine used for sending messages through a socket
     */
    void sendMessageInternal(Message* msg, boost::asio::local::stream_protocol::socket* socket);

    /**
     * Internal function to read raw data from the socket
     */
    void readData(boost::asio::local::stream_protocol::socket *socket_, boost::asio::streambuf *buf);

};


#endif //MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H
