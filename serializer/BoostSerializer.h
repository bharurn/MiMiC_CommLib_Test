//
// Created by bolnykh on 12/11/15.
//

#ifndef MIMICCOMMLIB_BOOSTSERIALIZER_H
#define MIMICCOMMLIB_BOOSTSERIALIZER_H


#include "../Serializer.h"
#include "../SystemData.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

/**
 * Serializer implementation using boost serialization mechanism
 */
class BoostSerializer : public Serializer {

    virtual void serialize(Message *msg, std::ostream *stream) override;

    virtual Message * deserealize(std::istream *data) override;
};

namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive &archive, Message &m, const unsigned int version) {

            archive.template register_type<SystemData>();
            archive.template register_type<FloatArrayData>();
            archive & m.data;
            archive & m.sender_id;
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
