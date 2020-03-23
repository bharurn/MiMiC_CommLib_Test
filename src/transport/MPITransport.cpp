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

#include "MPITransport.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>

const std::string MPITransport::FILENAME = ".portname";

void MPITransport::setTimeout() {
    this->timeout = TIMEOUT_DEFAULT;
    auto chars = std::getenv(TIMEOUT_KEY);
    if (chars == nullptr) {
        return;
    }
    std::string timeoutString = std::string(chars);

    bool isNumber = !timeoutString.empty() &&
                    std::find_if(timeoutString.begin(),
                                 timeoutString.end(),
                                 [](char c) { return !std::isdigit(c); }) == timeoutString.end();


    if (isNumber) {
        this->timeout = std::stoi(timeoutString);
    }
}

void MPITransport::initServer(const std::vector<std::string> paths) {
    this->setTimeout();
    uint client_number = (unsigned int) paths.size();
    ports.reserve(client_number + 1);
    intercomm.reserve(client_number + 1);
    ports.push_back(Port{});
    intercomm.push_back(this->host_comm);
    for (uint i = 0; i < client_number; ++i) {
        Port port{};
        MPI_Open_port(MPI_INFO_NULL, port.name);
        ports.push_back(port);
        std::string filepath = paths[i];
        filepath.append(FILENAME);
        std::remove(filepath.c_str());
        std::fstream f(filepath, std::fstream::out);
        if (f.is_open()) {
            f << port.name;
            f.close();
        }
    }
}

void MPITransport::initClient(const std::string path) {
    this->setTimeout();
    std::string port_file = path;
    port_file.append(FILENAME);

    ports.reserve(1);
    intercomm.reserve(1);
    intercomm.push_back(MPI_Comm());

    bool file_exists = false;
    while (!file_exists) {
        Port port{};
        std::fstream f(port_file, std::fstream::in);
        if (f.good()) {
            file_exists = true;
            f >> port.name;
            ports.push_back(port);
            f.close();
        }
    }
}

int MPITransport::connectAddress(int id) {
    auto result = std::async(std::launch::async,
                             MPI_Comm_connect,
                             ports[id].name,
                             MPI_INFO_NULL,
                             0,
                             host_comm,
                             &intercomm[id]);
    checkTimeout(result, ports[id].name);
    return result.get();
}

int MPITransport::acceptConnection(int id) {
    auto result = std::async(std::launch::async,
                             MPI_Comm_accept,
                             ports[id].name,
                             MPI_INFO_NULL,
                             0,
                             host_comm,
                             &intercomm[id]);
    checkTimeout(result, ports[id].name);
    return result.get();
}

void MPITransport::closeConnection(int id) {
    MPI_Comm_disconnect(&intercomm[id]);
}

void MPITransport::sendData(void *data, DataType type, int count, int id) {
    MPI_Ssend(data, count, pick_mpi_type(type), 0, 0, intercomm[id]);
}

void MPITransport::receiveData(void *data_holder, DataType type, int count, int id) {
    MPI_Status status;
    MPI_Recv(data_holder, count, pick_mpi_type(type), 0, MPI_ANY_TAG, intercomm[id], &status);
}

int MPITransport::probe(int id, DataType type) {
    int size;
    MPI_Status status;
    MPI_Probe(0, MPI_ANY_TAG, intercomm[id], &status);
    MPI_Get_count(&status, pick_mpi_type(type), &size);
    return size;
}

void MPITransport::destroy(int id, std::string path) {
    MPI_Close_port(ports[id].name);
    std::string filepath = path.append(FILENAME);
    remove(filepath.c_str());
}

MPI_Datatype MPITransport::pick_mpi_type(DataType type) {
    MPI_Datatype send_type;
    switch (type) {
        case TYPE_CHAR:
            send_type = MPI_CHARACTER;
            break;

        case TYPE_INT:
            send_type = MPI_INT;
            break;

        case TYPE_LONG:
            send_type = MPI_LONG;
            break;

        case TYPE_DOUBLE:
            send_type = MPI_DOUBLE;
            break;

        case TYPE_FLOAT:
            send_type = MPI_FLOAT;
            break;

        default:
            send_type = MPI_CHAR;
    }
    return send_type;
}

void MPITransport::prepare(void *args) {

}
