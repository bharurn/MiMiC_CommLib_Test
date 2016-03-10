//
// Created by bolnykh on 12/11/15.
//

#ifndef MIMICCOMMLIB_BOOSTSERIALIZER_H
#define MIMICCOMMLIB_BOOSTSERIALIZER_H


#include "Serializer.h"
#include "../message/SystemData.h"
#include "../message/ClientData.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

/**
 * Serializer implementation using boost serialization mechanism
 * KNOWN ISSUE: HETEROGENEOUS ARCHITECTURES ARE NOT SUPPORTED
 */
class BoostSerializer : public Serializer {

    void serialize(Message *msg, std::ostream *stream);

    Message * deserealize(std::istream *data);
};

namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive &archive, Message &m, const unsigned int version) {
            archive & m.data;
            archive & m.sender_id;
            archive & m.message_code;
//            archive & make_array<float>(m.data, m.size);
        }

        template<class Archive1>
        void serialize(Archive1 &archive, BaseMessageData &m, const unsigned int version) {
            archive & m.type;
            archive & m.entity_number;
        }

        template<class Archive>
        void serialize(Archive &archive, FloatArrayData &m, const unsigned int version) {
            archive & boost::serialization::base_object<BaseMessageData>(m);
            archive & m.array;
        }

        template<class Archive>
        void serialize(Archive &archive, ClientData &m, const unsigned int version) {
            archive & boost::serialization::base_object<BaseMessageData>(m);
            archive & m.clientId;
            archive & m.clientAddress;
            archive & m.clientPath;
        }
    }

    template<class Archive>
    void serialize(Archive &archive, SystemData &m, const unsigned int version) {
        archive & boost::serialization::base_object<BaseMessageData>(m);
        archive & m.indices;
        archive & m.types;
        archive & m.coordinates;
        archive & m.masses;
        archive & m.multipole_order;
    }

}



#endif //MIMICCOMMLIB_BOOSTSERIALIZER_H
