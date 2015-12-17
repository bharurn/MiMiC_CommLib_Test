//
// Created by bolnykh on 12/14/15.
//

#ifndef MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H
#define MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H


#include <boost/asio/local/stream_protocol.hpp>
#include "Transport.h"

class BoostSocketTransport : public Transport {

public:
    BoostSocketTransport(Serializer *serializer) : Transport(serializer) { }
    const static long BUFFER_SIZE = 1 * 1024 * 1024;

private:
    virtual void initServ(int clients_number, const char* file, std::map<int, Message*> replies) override;

    virtual void initClient() override;

    virtual void sendMessage(Message *msg) override;

    void sendMessageInternal(Message* msg, boost::asio::local::stream_protocol::socket* socket);

    char* readData(boost::asio::local::stream_protocol::socket* socket_);

};


#endif //MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H
