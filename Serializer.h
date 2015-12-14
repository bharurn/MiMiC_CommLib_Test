//
// Created by bolnykh on 12/7/15.
//

#include "Message.h"
#include "FloatArrayData.h"
#include <ostream>
#include <istream>

#ifndef MIMICCOMMLIB_SERIALIZER_H
#define MIMICCOMMLIB_SERIALIZER_H

class Serializer {

public:
    virtual void serialize(Message *msg, std::ostream *stream) {}
    virtual Message * deserealize(std::istream *data) {}

};
#endif //MIMICCOMMLIB_SERIALIZER_H
