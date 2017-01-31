//
// Created by bolnykh on 2/29/16.
//

#include "BaseMessageData.h"

#ifndef MIMICCOMMLIB_CLIENTDATA_H
#define MIMICCOMMLIB_CLIENTDATA_H

struct ClientData : public BaseMessageData {
    std::string clientPath;
    std::string clientAddress;
    int clientId;
};

#endif //MIMICCOMMLIB_CLIENTDATA_H
