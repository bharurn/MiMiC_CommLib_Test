#include <iostream>
#include "transport/SocketTransport.h"
#include "JsonSerializer.h"

using namespace std;

int main() {
    char buffer[1024];
    fgets(buffer, 80, stdin);
    string str = buffer;
    SocketTransport *transport = new SocketTransport(new JsonSerializer(), 29);
    if (str.compare("server\n") == 0) {
        transport->initServ();
    }
    else {
        Message *message = new Message();
        transport->initClient();
        transport->sendMessage(*message);
    }
    return 0;
}