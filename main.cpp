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
    int size = 1000;
    Transport *transport = new BoostSocketTransport(new BoostSerializer());
    if (str.compare("server\n") == 0) {
        transport->initServ();
    }
    else {
        transport->initClient();
//        Message *message = new Message();
//        float* array = new float[size];
//        for (int i = 0; i < size; ++i) {
//            array[i] = i;
//        }
////        std::copy(array.begin(), array.end(), message->data);
//        FloatArrayData* data = new FloatArrayData(1, size);
//        std::vector<double> vector1 = *new std::vector<double>(size);
//        vector1.assign(array, array+size);
//        data->array = vector1;
//        message->data = data;
//        transport->initClient();
//        transport->sendMessage(*message);
    }
    return 0;
}