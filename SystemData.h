//
// Created by bolnykh on 12/14/15.
//

#include <boost/serialization/array.hpp>
#include "BaseMessageData.h"

#ifndef MIMICCOMMLIB_SYSTEMDATA_H
#define MIMICCOMMLIB_SYSTEMDATA_H

class SystemData : public BaseMessageData {

public:
    SystemData() : BaseMessageData() { }

    SystemData(int type, int entity_number) : BaseMessageData(type, entity_number) {
    }

    std::vector<int> indices;
    std::vector<std::string> types;
    std::vector<double> coordinates;
    std::vector<double> masses;
    int multipole_order;
};

#endif //MIMICCOMMLIB_SYSTEMDATA_H
