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

#include "MPMDTransport.hpp"

void MPMDTransport::prepare(void *args) {
    int *color;
    int flag;
    MPI_Comm_get_attr(this->host_comm, MPI_APPNUM, &color, &flag);
    MPI_Comm_split(this->host_comm, *color, 0, &this->local_comm);
    MPI_Comm_dup(this->local_comm, static_cast<MPI_Comm *>(args));
}

void MPMDTransport::initServer(std::vector<std::string> paths) {
    std::vector<int> ranks(paths.size() + 1);

    int ownRank;
    MPI_Comm_rank(this->host_comm, &ownRank);

    ranks[0] = ownRank;
    for (int i = 0; i < paths.size(); ++i) {
        MPI_Status status;

        int size;
        MPI_Probe(MPI_ANY_SOURCE, CLIENT_IDENTIFY_TAG, this->host_comm, &status);
        int rank = status.MPI_SOURCE;
        MPI_Get_count(&status, MPI_CHAR, &size);
        char path[size];
        MPI_Recv(&path, size, MPI_CHAR, rank, CLIENT_IDENTIFY_TAG, this->host_comm, &status);
        std::string temp = path;
        temp = temp.substr(0, size);

        for (int j = 0; j < paths.size(); j++) {
            if (paths[j] == temp) {
                ranks[j + 1] = rank;
                break;
            }
        }
    }

    for (int i = 0; i < paths.size(); ++i) {
        int intercommSize = ranks.size();
        MPI_Ssend(&intercommSize, 1, MPI_INT, ranks[i + 1], CLIENT_COUNT_TAG, this->host_comm);
        MPI_Ssend(&(*ranks.begin()), ranks.size(), MPI_INT, ranks[i + 1], CLIENT_LIST_TAG, this->host_comm);
    }

    MPI_Group world;
    MPI_Comm_group(this->host_comm, &world);

    MPI_Group intercommGroup;
    MPI_Group_incl(world, ranks.size(), &(*ranks.begin()), &intercommGroup);
    MPI_Comm intercomm;
    MPI_Comm_create_group(this->host_comm, intercommGroup, 1, &intercomm);
    this->intercomm.push_back(intercomm);
}

void MPMDTransport::initClient(std::string path) {
    MPI_Group world, local, diff;
    MPI_Comm_group(this->host_comm, &world);
    MPI_Comm_group(this->local_comm, &local);

    MPI_Group_difference(world, local, &diff);

    int diffSize;
    MPI_Group_size(diff, &diffSize);

    std::vector<int> diffRanks(diffSize);
    std::vector<int> hostRanks(diffSize);
    for (int i = 0; i < diffSize; ++i) {
        diffRanks[i] = i;
    }

    MPI_Group_translate_ranks(diff, diffSize, &(*diffRanks.begin()), world, &(*hostRanks.begin()));

    int worldRank;
    MPI_Comm_rank(this->host_comm, &worldRank);

    MPI_Request requests[diffSize];
    for (int i = 0; i < diffSize; i++) {
        MPI_Isend(path.c_str(),
                  path.length(),
                  MPI_CHAR,
                  hostRanks[i],
                  CLIENT_IDENTIFY_TAG,
                  this->host_comm,
                  &requests[i]);
    }

    int successful = MPI_UNDEFINED;
    MPI_Status status;
    MPI_Waitany(diffSize, requests, &successful, &status);

    for (int i = 0; i < diffSize; ++i) {
        if (i != successful) {
            MPI_Cancel(&requests[i]);
            MPI_Request_free(&requests[i]);
        }
    }

    int intercommSize;
    MPI_Recv(&intercommSize, 1, MPI_INT, MPI_ANY_SOURCE, CLIENT_COUNT_TAG, this->host_comm, &status);
    int remoteHost = status.MPI_SOURCE;

    int intercommRanks[intercommSize];
    MPI_Recv(&intercommRanks, intercommSize, MPI_INT, remoteHost, CLIENT_LIST_TAG, this->host_comm, &status);

    MPI_Group intercommGroup;
    MPI_Group_incl(world, intercommSize, intercommRanks, &intercommGroup);
    MPI_Comm intercomm;
    MPI_Comm_create_group(this->host_comm, intercommGroup, 1, &intercomm);
    this->intercomm.push_back(intercomm);
}

void MPMDTransport::sendData(void *data, DataType type, int count, int id) {
    MPI_Ssend(data, count, pick_mpi_type(type), id, 0, this->intercomm[0]);
}

void MPMDTransport::receiveData(void *data_holder, DataType type, int count, int id) {
    MPI_Status status;
    MPI_Recv(data_holder, count, pick_mpi_type(type), id, MPI_ANY_TAG, this->intercomm[0], &status);
}

int MPMDTransport::probe(int id, DataType type) {
    int size;
    MPI_Status status;
    MPI_Probe(id, MPI_ANY_TAG, intercomm[0], &status);
    MPI_Get_count(&status, pick_mpi_type(type), &size);
    return size;
}

int MPMDTransport::connectAddress(int id) {
    // No need to do anything here
    return 0;
}

int MPMDTransport::acceptConnection(int id) {
    // No need to do anything here
    return 0;
}

void MPMDTransport::closeConnection(int id) {
    // No need to do anything here
}

void MPMDTransport::destroy(int id, std::string path) {

}
