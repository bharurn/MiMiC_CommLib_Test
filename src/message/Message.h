//
// Created by bolnykh on 12/7/15.
//

#ifndef MIMICCOMMLIB_MESSAGE_H
#define MIMICCOMMLIB_MESSAGE_H

#include "BaseMessageData.h"
#include "FloatArrayData.h"
#include "SystemData.h"

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

    static const int OK_CODE = 1;

    static const int FAIL_CODE = -1;
};



#endif //MIMICCOMMLIB_MESSAGE_H