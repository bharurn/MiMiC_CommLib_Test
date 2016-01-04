//
// Created by bolnykh on 12/14/15.
//

#include <boost/serialization/array.hpp>
#include "BaseMessageData.h"

#ifndef MIMICCOMMLIB_SYSTEMDATA_H
#define MIMICCOMMLIB_SYSTEMDATA_H

/**
 * Class encapsulatin the data about the system of the client code
 */
struct SystemData : public BaseMessageData {

public:
    SystemData() : BaseMessageData() { }

    SystemData(int type, int entity_number) : BaseMessageData(type, entity_number) {
    }

    /**
     * Atom indices
     */
    std::vector<int> indices;

    /**
     * Atom types
     */
    std::vector<std::string> types;

    /**
     * Coordinates of items mapped onto 1D array
     */
    std::vector<double> coordinates;

    /**
     * Atom masses
     */
    std::vector<double> masses;

    /**
     * Maximum order of multipoles that is used by the code
     */
    int multipole_order;

};

#endif //MIMICCOMMLIB_SYSTEMDATA_H
