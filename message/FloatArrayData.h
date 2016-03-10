//
// Created by bolnykh on 12/14/15.
//

#include "BaseMessageData.h"
#include <vector>

#ifndef MIMICCOMMLIB_FLOATARRAYDATA_H
#define MIMICCOMMLIB_FLOATARRAYDATA_H

/**
 * Class for sending an array of doubles (like coordinates)
 */
struct FloatArrayData : public BaseMessageData {
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
