//
// Created by bolnykh on 12/14/15.
//

#ifndef MIMICCOMMLIB_MESSAGEDATA_H
#define MIMICCOMMLIB_MESSAGEDATA_H


class BaseMessageData {
public:
    int type;
    int entity_number;

    BaseMessageData() { }

    BaseMessageData(int type, int entity_number) : type(type), entity_number(entity_number) { }

//    template<class Archive>
//    virtual void serialize_private(Archive &archive, BaseMessageData &m, const unsigned int version) { }


};
#endif //MIMICCOMMLIB_MESSAGEDATA_H
