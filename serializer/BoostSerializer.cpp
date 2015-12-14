//
// Created by bolnykh on 12/11/15.
//

#include <sstream>
#include "BoostSerializer.h"



void BoostSerializer::serialize(Message *msg, std::ostream *stream) {
    boost::archive::text_oarchive oa(*stream);
    // write class instance to archive
    oa << msg;
}


Message * BoostSerializer::deserealize(std::istream *data) {
    boost::archive::text_iarchive ia(*data);
    // read class state from archive
    Message* msg;
    ia >> msg;
    return msg;
}
