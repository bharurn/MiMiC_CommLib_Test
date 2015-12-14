//
// Created by bolnykh on 12/7/15.
//

#ifndef MIMICCOMMLIB_MESSAGE_H
#define MIMICCOMMLIB_MESSAGE_H

#include <assert.h>
#include <boost/serialization/array.hpp>
#include <type_traits>
#include "BaseMessageData.h"
#include "FloatArrayData.h"
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>

class Message {
public:
    FloatArrayData* data;
    char* target; //perhaps not needed

    Message() : data(nullptr), target(nullptr) { }

};



#endif //MIMICCOMMLIB_MESSAGE_H