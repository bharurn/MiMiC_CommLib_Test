//
// Created by bolnykh on 12/7/15.
//

#include <zconf.h>
#include "../Message.h"
#include "../Serializer.h"
#include <map>

#ifndef MIMICCOMMLIB_TRANSPORT_H
#define MIMICCOMMLIB_TRANSPORT_H

class  Transport {

protected:
    Serializer *serializer;

public:
    Transport(Serializer *serializer) : serializer(serializer) { }
    virtual void initServ(int clients_number, const char* file, std::map<int, Message*> replies) {}
    virtual void initClient() {}
    virtual void sendMessage(Message *msg) {}

    void setSerializer(Serializer *serializer) {
        Transport::serializer = serializer;
    }
};
#endif //MIMICCOMMLIB_TRANSPORT_H