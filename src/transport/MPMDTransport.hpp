//
//    MCL: MiMiC Communication Library
//    Copyright (C) 2015-2020  Viacheslav Bolnykh,
//                             Jógvan Magnus Haugaard Olsen,
//                             Simone Meloni,
//                             Emiliano Ippoliti,
//                             Paolo Carloni
//                             and Ursula Röthlisberger.
//
//    This file is part of MCL.
//
//    MCL is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as
//    published by the Free Software Foundation, either version 3 of
//    the License, or (at your option) any later version.
//
//    MCL is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef MIMICCOMMLIB_MPMDTRANSPORT_HPP
#define MIMICCOMMLIB_MPMDTRANSPORT_HPP

#include "Transport.h"
#include "DataTypes.h"
#include "MPITransport.h"

#include <mpi.h>

#include <csignal>
#include <iostream>
#include <future>

class MPMDTransport : public MPITransport {

public:

    explicit MPMDTransport(MPI_Comm comm) : MPITransport(comm){}

    ~MPMDTransport() override = default;

    void prepare(void *args) override;

    void initServer(std::vector<std::string> paths) override;

    void initClient(std::string path) override;

    void sendData(void *data, DataType type, int count, int id) override;

    void receiveData(void *data_holder, DataType type, int count, int id) override;

    int probe(int id, DataType type) override;

    int connectAddress(int id) override;

    int acceptConnection(int id) override;

    void closeConnection(int id) override;

    void destroy(int id, std::string path) override;

private:

    static constexpr int CLIENT_IDENTIFY_TAG = 12345;
    static constexpr int SERVER_IDENTIFY_TAG = CLIENT_IDENTIFY_TAG + 1;
    static constexpr int CLIENT_COUNT_TAG = SERVER_IDENTIFY_TAG + 1;
    static constexpr int CLIENT_LIST_TAG = CLIENT_COUNT_TAG + 1;
    static constexpr int CLIENT_ID_TAG = CLIENT_LIST_TAG + 1;

    /**
     * Local communicator handling communication within a single entity
     */
    MPI_Comm local_comm;

    enum EndpointType {
        TYPE_SERVER = 0,
        TYPE_CLIENT = 1
    };
};


#endif //MIMICCOMMLIB_MPMDTRANSPORT_HPP
