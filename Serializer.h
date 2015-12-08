//
// Created by bolnykh on 12/7/15.
//

#include "Message.h"

#ifndef MIMICCOMMLIB_SERIALIZER_H
#define MIMICCOMMLIB_SERIALIZER_H

class Serializer {

public:
    virtual char* serialize(Message msg) {}
    virtual Message deserealize(char* data) {}

};
#endif //MIMICCOMMLIB_SERIALIZER_H
