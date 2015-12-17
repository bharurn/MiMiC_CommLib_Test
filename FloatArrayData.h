//
// Created by bolnykh on 12/14/15.
//

#include <boost/serialization/base_object.hpp>
#include <assert.h>
#include <boost/serialization/array.hpp>
#include "BaseMessageData.h"

#ifndef MIMICCOMMLIB_FLOATARRAYDATA_H
#define MIMICCOMMLIB_FLOATARRAYDATA_H

/**
 * Class for sending an array of doubles (like coordinates)
 */
class FloatArrayData : public BaseMessageData {
public:
    /**
     * Array of double values to be sent
     */
    std::vector<double> array;

    FloatArrayData() : BaseMessageData() { }

    FloatArrayData(int type, int entity_number) : BaseMessageData(type, entity_number) {
    }



};
#endif //MIMICCOMMLIB_FLOATARRAYDATA_H
