//
// Created by bolnykh on 12/7/15.
//

#ifndef MIMICCOMMLIB_MESSAGE_H
#define MIMICCOMMLIB_MESSAGE_H

#include <assert.h>
#include <boost/serialization/array.hpp>
#include "BaseMessageData.h"
#include "FloatArrayData.h"
#include "SystemData.h"
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>

/**
 * A message class representing messages sent between processes.
 */
struct Message {
public:
    /**
     * Message data
     */
    BaseMessageData* data;

    /**
     * Id of the process that sent a message
     */
    int sender_id;

    int message_code;

    Message() { }

    const int OK_CODE = 1;

    const int FAIL_CODE = -1;
};



#endif //MIMICCOMMLIB_MESSAGE_H