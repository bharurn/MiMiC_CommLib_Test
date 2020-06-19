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

#include <algorithm>

#include "MessageApi.h"
#include "MCLMain.h"

#include "transport/MPITransport.h"
#include "transport/MPMDTransport.hpp"

#include <iostream>

/**
 * External API of the library
 * NOTE! ALL API CALLS ARE BLOCKING!!!
 */

/**
* \var string key used to retrieve communication mechanism
* environment variable.
*/
static constexpr auto COMMUNICATION_KEY = "MCL_COMM";

/**
* \var switch to MPI client-server mechanism
*/
static constexpr auto MCL_TR_MPI = 1;
/**
* \var switch to MPI MPMD mechanism
*/
static constexpr auto MCL_TR_MPMD = 2;

int MCL_init(void *param) {
    auto chars = std::getenv(COMMUNICATION_KEY);
    std::cout << "hi " << chars << '\n';
    if (chars != nullptr) {
        std::string string = std::string(chars);
   	std::cout << std::stoi(string) << '\n';
        switch (std::stoi(string)) {
            case MCL_TR_MPI:
                MCLMain::getInstance()
                        .setProtocol(new MPITransport(MPI_COMM_SELF));
                break;
            case MCL_TR_MPMD:
                MCLMain::getInstance()
                        .setProtocol(new MPMDTransport(*static_cast<MPI_Comm *>(param)));
                break;
            default:
                std::cerr << "MCL: Unknown communication mechanism is chosen! "
                             "MPMD Mechanism will be used instead" << std::endl;
                MCLMain::getInstance()
                        .setProtocol(new MPMDTransport(*static_cast<MPI_Comm *>(param)));
        }
    } else {
        MCLMain::getInstance()
                .setProtocol(new MPMDTransport(*static_cast<MPI_Comm *>(param)));
    }
    MCLMain::getInstance().prepare(param);
    std::cout << "init done\n";
    return 0;
}

int MCL_handshake(char *paths, char* delimeter, int isServer) {
    if (isServer) {
        MCL_init_server(paths, delimeter[0]);
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

