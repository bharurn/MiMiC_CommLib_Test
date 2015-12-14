//
// Created by bolnykh on 12/7/15.
//

#include <zconf.h>
#include "../Message.h"
#include "../Serializer.h"

#ifndef MIMICCOMMLIB_TRANSPORT_H
#define MIMICCOMMLIB_TRANSPORT_H

class  Transport {

protected:
    Serializer *serializer;

public:
    Transport(Serializer *serializer) : serializer(serializer) { }
    virtual void initServ() {}
    virtual void initClient() {}
    virtual void sendMessage(Message *msg) {}

    void setSerializer(Serializer *serializer) {
        Transport::serializer = serializer;
    }
};
#endif //MIMICCOMMLIB_TRANSPORT_H