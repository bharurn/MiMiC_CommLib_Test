//
// Created by bolnykh on 12/7/15.
//

#ifndef MIMICCOMMLIB_MESSAGESERVICE_H
#define MIMICCOMMLIB_MESSAGESERVICE_H


#include "transport/Transport.h"

/**
 * Singleton class representing messaging service used by the library (should be initialized)
 */
class MessageService {

private:
    Transport transport;

public:
    void sendMessage(Message message);

};


#endif //MIMICCOMMLIB_MESSAGESERVICE_H
