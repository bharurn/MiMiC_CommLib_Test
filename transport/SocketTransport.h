//
// Created by bolnykh on 12/7/15.
//

#ifndef MIMICCOMMLIB_SOCKETTRANSPORT_H
#define MIMICCOMMLIB_SOCKETTRANSPORT_H


#include <stdint.h>
#include "Transport.h"

class SocketTransport : Transport {

public:
    SocketTransport(Serializer *serializer) : Transport(serializer) { }

    SocketTransport(Serializer *serializer, int portNumber) : Transport(serializer), portNumber(portNumber) { }



    void setPortNumber(int portNumber) {
        SocketTransport::portNumber = portNumber;
    }

    virtual void initServ() override;

    virtual void sendMessage(Message msg) override;

    virtual void initClient() override;

private:
    uint16_t portNumber = -1;

};


#endif //MIMICCOMMLIB_SOCKETTRANSPORT_H
