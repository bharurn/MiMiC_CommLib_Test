//
// Created by bolnykh on 12/7/15.
//

#ifndef MIMICCOMMLIB_MESSAGE_H
#define MIMICCOMMLIB_MESSAGE_H

struct Message {
    int type;
    float data[];
    char* target; //perhaps not needed
};

#endif //MIMICCOMMLIB_MESSAGE_H