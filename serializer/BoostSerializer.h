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

class BoostSerializer : public Serializer {

    virtual void serialize(Message *msg, std::ostream *stream) override;

    virtual Message * deserealize(std::istream *data) override;
};

namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive &archive, Message &m, const unsigned int version) {
            if (Archive::is_loading::value)
            {
                assert(m.data == nullptr);
                m.data = new SystemData();
            }
            archive & m.data;
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
//            if (Archive::is_loading::value)
//            {
//                m.array = *new std::vector(m.entity_number);
//            }
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
//        if (Archive::is_loading::value)
//        {
//            assert(m.indices == nullptr);
//            m.indices = new int[m.entity_number];
//            assert(m.types == nullptr);
//            m.types = new char[m.entity_number];
//            assert(m.coordinates == nullptr);
//            m.coordinates = new double[3*m.entity_number];
//            assert(m.masses == nullptr);
//            m.masses = new double[m.entity_number];
//        }
//        archive & boost::serialization::make_array<int>(m.indices, m.entity_number);
//        archive & boost::serialization::make_array<const char>(m.types, m.entity_number);
//        archive & boost::serialization::make_array<double>(m.coordinates, 3*m.entity_number);
//        archive & boost::serialization::make_array<double>(m.masses, m.entity_number);
    }
}



#endif //MIMICCOMMLIB_BOOSTSERIALIZER_H
