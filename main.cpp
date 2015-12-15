#include <iostream>
#include "transport/SocketTransport.h"
#include "serializer/BoostSerializer.h"
#include "FloatArrayData.h"
#include "transport/BoostSocketTransport.h"

using namespace std;

int main() {
    char buffer[1024];
    fgets(buffer, 80, stdin);
    string str = buffer;
    int size = 100000;
    Transport *transport = new BoostSocketTransport(new BoostSerializer());
    if (str.compare("server\n") == 0) {
        transport->initServ();
    }
    else {
        transport->initClient();
        Message *message = new Message();
        float* array = new float[size];
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
        vector1.assign(array, array+size);
        data->indices = indices;
        data->types = types;
        data->coordinates = coordinates;
        data->masses = masses;
//        data->array = vector1;
        message->data = data;
//        transport->initClient();
        transport->sendMessage(message);
    }
    return 0;
}