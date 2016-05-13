#include <iostream>
#include <mpi.h>
#include <sys/time.h>
#include <stdlib.h>
#include "MessageApi.h"
#include "DataTypes.h"

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
        int size = 200000000;
        if (str.compare("server\n") == 0) {
            char* clients[2];
            clients[0] = "./client1";
            clients[1] = "./client2/";
            char* delimeter = ";";
            int data_type = TYPE_DOUBLE;
            int client = 1;
            MCL_init_server(&client, "./client1", delimeter);
            double* data = (double *) malloc(sizeof(double) * size);
            MCL_receive(data, &size, &data_type, &client);
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
                int data_type = TYPE_DOUBLE;
                int client = 1;
                timestamp_t t0 = get_timestamp();
                MCL_send(test, &size, &data_type, &client);
                timestamp_t t1 = get_timestamp();
                cout << "Total execution time: " << t1-t0 << "\n";
            }
            MCL_destroy();
        }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}