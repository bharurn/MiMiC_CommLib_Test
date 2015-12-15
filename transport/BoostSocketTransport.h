//
// Created by bolnykh on 12/14/15.
//

#ifndef MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H
#define MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H


#include "Transport.h"

class BoostSocketTransport : public Transport {

public:
    friend class session;
    BoostSocketTransport(Serializer *serializer) : Transport(serializer) { }
    const static long BUFFER_SIZE = 1 * 1024 * 1024;

private:
    virtual void initServ() override;

    virtual void initClient() override;

    virtual void sendMessage(Message *msg) override;
};


#endif //MIMICCOMMLIB_BOOSTSOCKETTRANSPORT_H
