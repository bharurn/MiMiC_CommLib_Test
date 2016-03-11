#include <iostream>
#include <mpi.h>
#include <sys/time.h>
#include <stdlib.h>
#include "MessageApi.h"

using namespace std;

typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp ()
{
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

int main() {
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        char buffer[1024];
        fgets(buffer, 80, stdin);
        string str = buffer;
        int size = 10000000;
        if (str.compare("server\n") == 0) {
            char* clients[2];
            clients[0] = "./client1";
            clients[1] = "./client2/";
            MCL_init_server(1, clients);
            double* data = (double *) malloc(sizeof(double) * size);
            MCL_receive(data, size, TYPE_DOUBLE, 1);
            for (int i = 0; i < 2; ++i) {
                std::cout << data[i] << "\n";
            }
            MCL_destroy();
        }
        else {
            std::string path;
            if (strcmp(str.c_str(), "asdf\n") == 0) {
                path = "./client1/";
            } else {
                path = "./client2/";
            }

            std::cout << "init\n";
            MCL_init_client((char *) path.c_str());
            if (strcmp(str.c_str(), "asdf\n") == 0) {
                double* test = (double *) malloc(sizeof(double) * size);

                for (int i = 0; i < size; ++i) {
                    test[i] = i * 0.2;
                }

                timestamp_t t0 = get_timestamp();
                MCL_send(test, size, TYPE_DOUBLE, 0);
                timestamp_t t1 = get_timestamp();
                cout << "Total execution time: " << t1-t0 << "\n";
            }
            MCL_destroy();
            /*RawDataStruct* test = client.requestRaw(0, TYPE_DOUBLE);
            double* data = (double *) test->data;
            for (int i = 0; i < test->count; ++i) {
                std::cout << data[i] << "\n";
            }
            client.sendRaw(data, 2, 0, TYPE_DOUBLE);*/
//        client.connect(0);

//        Message *message = new Message();
//        message->sender_id = 1;
//        std::vector<int> indices;
//        std::vector<std::string> types;
//        std::vector<double> coordinates;
//        std::vector<double> masses;
//        for (int i = 0; i < size; ++i) {
//            indices.push_back(i);
//            types.push_back("Na");
//            coordinates.push_back(i*3);
//            coordinates.push_back(i*6);
//            coordinates.push_back(i*9);
//            masses.push_back(i*20);
//        }
//        std::copy(array.begin(), array.end(), message->data);
//        SystemData* data = new SystemData(1, size);
//        std::vector<double> vector1 = *new std::vector<double>(size);
//        data->indices = indices;
//        data->types = types;
//        data->coordinates = coordinates;
//        data->masses = masses;
//        data->multipole_order = 4;
//        data->array = vector1;
//        message->data = data;
//        client.send(message, 0);
            /*transport->initClient();
            Message *message = new Message();
            message->sender_id = 1;
            std::vector<int> indices;
            std::vector<std::string> types;
            std::vector<double> coordinates;
            std::vector<double> masses;
            for (int i = 0; i < size; ++i) {
                indices.push_back(i);
                types.push_back("Na");
                coordinates.push_back(i*3);
                coordinates.push_back(i*6);
                coordinates.push_back(i*9);
                masses.push_back(i*20);
            }
    //        std::copy(array.begin(), array.end(), message->data);
            SystemData* data = new SystemData(1, size);
            std::vector<double> vector1 = *new std::vector<double>(size);
            data->indices = indices;
            data->types = types;
            data->coordinates = coordinates;
            data->masses = masses;
            data->multipole_order = 4;
    //        data->array = vector1;
            message->data = data;
    //        transport->MCL_init_client();
            transport->sendMessage(message, "f");*/
        }
//    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}