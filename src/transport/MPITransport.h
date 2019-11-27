//
//    MCL: MiMiC Communication Library
//    Copyright (C) 2015-2017  Viacheslav Bolnykh,
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

#ifndef MIMICCOMMLIB_MPITRANSPORT_H
#define MIMICCOMMLIB_MPITRANSPORT_H


#include "Transport.h"
#include "DataTypes.h"
#include <mpi.h>

/**
 * Transport implementation using MPI intercommunicators
 */
class MPITransport : public Transport {

    typedef char mpi_port_name[MPI_MAX_PORT_NAME];

public:
    explicit MPITransport(MPI_Comm comm) : Transport(), host_comm(comm) { }

    ~MPITransport() override = default;

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
    class Port {
    public:
        mpi_port_name name;
    };

    static MPI_Datatype pick_mpi_type(DataType type);

    /**
     * Communicator to which a remote group will be attached
     */
    MPI_Comm host_comm;

    /**
     * Array of intercommunicators that will handle connections
     */
    std::vector<MPI_Comm>intercomm;

    /**
     * Name of the file used to share port address
     */
    const static std::string FILENAME;

    /**
     * Array of ports used to connect clients
     */
    std::vector<Port> ports;
};


#endif //MIMICCOMMLIB_MPITRANSPORT_H
