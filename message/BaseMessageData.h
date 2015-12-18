//
// Created by bolnykh on 12/14/15.
//

#ifndef MIMICCOMMLIB_MESSAGEDATA_H
#define MIMICCOMMLIB_MESSAGEDATA_H

/**
 * Abstract class for data contained in the message
 */
class BaseMessageData {
public:
    /**
     * Type of the message (probably not needed anymore)
     */
    int type;

    /**
     * Number of entities contained in this chunk of data (will be needed if we are forced to work with c++98)
     */
    int entity_number;

    BaseMessageData() { }

    BaseMessageData(int type, int entity_number) : type(type), entity_number(entity_number) { }
    virtual ~BaseMessageData(){};

};
#endif //MIMICCOMMLIB_MESSAGEDATA_H
