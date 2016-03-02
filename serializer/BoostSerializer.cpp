//
// Created by bolnykh on 12/11/15.
//

#include <sstream>
#include <boost/serialization/export.hpp>
#include "BoostSerializer.h"


BOOST_CLASS_EXPORT(SystemData)
BOOST_CLASS_EXPORT(FloatArrayData)
BOOST_CLASS_EXPORT(ClientData)

void BoostSerializer::serialize(Message *msg, std::ostream *stream) {
    boost::archive::binary_oarchive oa(*stream);
    // write class instance to archive
    oa << msg;
}


Message * BoostSerializer::deserealize(std::istream *data) {
    boost::archive::binary_iarchive ia(*data);
    // read class state from archive
    Message* msg;
    ia >> msg;
    return msg;
}
