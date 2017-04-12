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

#ifndef MIMICCOMMLIB_MCLMAIN_H
#define MIMICCOMMLIB_MCLMAIN_H

#include "transport/Endpoint.h"
#include "transport/Client.h"
#include "transport/Server.h"
#include <sstream>
#include <iterator>

/**
 * Main class of the MCL - mostly needed in order to simplify testing
 */
template <typename _Transport>
class MCLMain {

private:
    Endpoint* endpoint;
    _Transport* protocol;

    MCLMain() {};
//    MCLMain(MCLMain<_Transport> const&);
    void operator=(MCLMain<_Transport> const&);

public:
    static MCLMain<_Transport>& getInstance() {
        static MCLMain<_Transport> instance;
        return instance;
    }

    void setProtocol(_Transport* protocol) {
        this->protocol = protocol;
    }

    int initServer(char *paths_string, char delimeter) {
        std::string merged_paths = std::string(paths_string);
        std::stringstream ss(merged_paths);
        std::string path;
        std::vector<std::string> client_paths;
        while (std::getline(ss, path, delimeter)) {
            if (!path.empty()) {
                client_paths.push_back(path);
            }
        }

        Server* server = new Server(this->protocol);
        server->setId(0);
        this->endpoint = server;

        server->init(client_paths);
        server->handshake();
        return 0;
    }

    void initClient(char *path) {
        std::string client_path = std::string(path);
        std::vector<std::string> paths;
        paths.push_back(client_path);

        Client* client = new Client(this->protocol);
        this->endpoint = client;

        client->init(paths);
        client->handshake();
    }

    void send(void *data, int count, int data_type, int destination) {
        int temp_type = data_type;
        DataType type = static_cast<DataType>(temp_type);
        this->endpoint->send(data, count, destination, type);
    }

    void receive(void *buffer, int count, int data_type, int source) {
        int temp_type = data_type;
        DataType type = static_cast<DataType>(temp_type);
        endpoint->request(buffer, count, source, type);
    }

    void destroy() {
        endpoint->destroy();
    }

};


#endif //MIMICCOMMLIB_MCLMAIN_H
