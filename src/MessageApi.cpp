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

#include "mpi.h"

#include "MessageApi.h"
#include "MCLMain.h"

#include "transport/MPITransport.h"
#include "transport/MPMDTransport.hpp"

/**
 * External API of the library
 * NOTE! ALL API CALLS ARE BLOCKING!!!
 */

int MCL_init(void *param) {
#ifdef MCL_MPI
    MCLMain::getInstance().setProtocol(new MPITransport(MPI_COMM_SELF));
#elif MCL_MPMD
    MCLMain::getInstance().setProtocol(new MPMDTransport(*static_cast<MPI_Comm *>(param)));
#else
    std::err << "MCL: Communication mechanism has not been configured. "
                 "Please recompile the library!" << std::endl;
#endif
    MCLMain::getInstance().prepare(param);
    return 0;
}

int MCL_handshake(char *paths, char delimeter, int isServer) {
    if (isServer) {
        MCL_init_server(paths, delimeter);
    } else {
        MCL_init_client(paths);
    }
    return 0;
}

int MCL_init_server(char *paths_string, char delimeter) {
    return MCLMain::getInstance().initServer(paths_string, delimeter);
}

void MCL_init_client(char *path) {
    MCLMain::getInstance().initClient(path);
}

void MCL_send(void *data, int count, int data_type, int destination) {
    MCLMain::getInstance().send(data, count, data_type, destination);
}

void MCL_receive(void *buffer, int count, int data_type, int source) {
    MCLMain::getInstance().receive(buffer, count, data_type, source);
}

void MCL_destroy() {
    MCLMain::getInstance().destroy();
}

