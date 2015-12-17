//
// Created by bolnykh on 12/7/15.
//

#include "Message.h"
#include "FloatArrayData.h"
#include <ostream>
#include <istream>

#ifndef MIMICCOMMLIB_SERIALIZER_H
#define MIMICCOMMLIB_SERIALIZER_H

/**
 * Abstract class of serializer used to pack and unpack data from a parcel to be sent
 * over transport protocol
 */
class Serializer {

public:
    /**
     * Serialize data and put it into a stream
     *
     * \param msg message to be serialized
     * \param stream output strem in which to put data
     */
    virtual void serialize(Message *msg, std::ostream *stream) {}

    /**
     * Deserialize data from stream
     *
     * \param stream with serialized data
     * \return Message contained in serialized data
     */
    virtual Message * deserealize(std::istream *data) {}

};
#endif //MIMICCOMMLIB_SERIALIZER_H
