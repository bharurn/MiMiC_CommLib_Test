#include <iostream>
#include <mpi.h>
#include "transport/SocketTransport.h"
#include "serializer/BoostSerializer.h"
#include "message/FloatArrayData.h"
#include "transport/BoostSocketTransport.h"
#include "transport/Endpoint.h"
#include "transport/Server.h"
#include "transport/MPITransport.h"

using namespace std;

int main() {
    MPI_Init(NULL, NULL);
    char buffer[1024];
    fgets(buffer, 80, stdin);
    string str = buffer;
    int size = 200;
    Transport *transport = new MPITransport(MPI_COMM_WORLD);
    if (str.compare("server\n") == 0) {
        /*std::map<int, Message*> reply_map;

        Message *message = new Message();
        std::vector<double> array(size);
        for (int i = 0; i < size; ++i) {
            array.push_back(i);
        }
        FloatArrayData* data = new FloatArrayData();
        data->array = array;

        reply_map[1] = message;
        reply_map[2] = message;

        transport->initServ();*/
        char* clients[1];
        clients[0] = "./demo_socket";

        Server server = Server(transport, "./demo_socket");
        server.init("sdsfdg", *transport, 1, clients);
        server.handshake();
        double test[2];
        test[0] = 0.3;
        test[1] = 0.8;
        server.sendRaw(test, 2, 1, TYPE_DOUBLE);
//        server.connect(1);
//        Message* msg = server.request(1);
//        SystemData* data = (SystemData*) msg->data;
//        msg->message_code = 2;
    }
    else {
        Client client = Client(transport);
        client.setAddress("./demo_socket");
        client.setPath("./demo_socket");
        client.setPath_size(13);
        client.setAddress_size(13);
        std::cout << "init\n";
        client.init("sdfgsd", *transport);
        std::cout << "handshake\n";
        client.handshake();
        std::cout << "handshake end id: " << client.getId() << " \n";
        RawDataStruct* test = client.requestRaw(0, TYPE_DOUBLE);
        double* data = (double *) test->data;
        for (int i = 0; i < test->count; ++i) {
            std::cout << data[i] << "\n";
        }
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
//        transport->initClient();
        transport->sendMessage(message, "f");*/
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}