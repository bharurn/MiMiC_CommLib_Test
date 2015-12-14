//
// Created by bolnykh on 12/14/15.
//

#include <boost/serialization/array.hpp>
#include "BaseMessageData.h"

#ifndef MIMICCOMMLIB_SYSTEMDATA_H
#define MIMICCOMMLIB_SYSTEMDATA_H

class SystemData : public BaseMessageData {

public:
    SystemData(int type, int entity_number) : BaseMessageData(type, entity_number) {
        indices = new int[entity_number];
        types = new char[entity_number];
        coordinates = new double[3*entity_number];
        masses = new double[entity_number];
    }

    int* indices;
    const char *types;
    double* coordinates;
    double* masses;
    int multipole_order;
};

#endif //MIMICCOMMLIB_SYSTEMDATA_H
