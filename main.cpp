#include <iostream>
#include "transport/SocketTransport.h"
#include "serializer/BoostSerializer.h"
#include "message/FloatArrayData.h"
#include "transport/BoostSocketTransport.h"
#include "transport/Endpoint.h"

using namespace std;

int main() {
    char buffer[1024];
    fgets(buffer, 80, stdin);
    string str = buffer;
    int size = 200;
    Transport *transport = new BoostSocketTransport(new BoostSerializer(), "./demo_socket");
    if (str.compare("server\n") == 0) {
        std::map<int, Message*> reply_map;

        Message *message = new Message();
        std::vector<double> array(size);
        for (int i = 0; i < size; ++i) {
            array.push_back(i);
        }
        FloatArrayData* data = new FloatArrayData();
        data->array = array;

        reply_map[1] = message;
        reply_map[2] = message;

        transport->initServ();
    }
    else {
        transport->initClient();
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
        transport->sendMessage(message);
    }
    return 0;
}