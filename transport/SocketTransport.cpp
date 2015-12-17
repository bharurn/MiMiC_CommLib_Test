//
// Created by bolnykh on 12/7/15.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include "SocketTransport.h"
#define UNIX_PATH_MAX    108

struct sockaddr_un address;
int socket_fd, connection_fd;
socklen_t address_length;
char* buffer;

void SocketTransport::handle_connection(int connection_fd) {
    int nbytes;
    nbytes = read(connection_fd, buffer, BUFFER_SIZE);
    buffer[nbytes] = 0;

    std::stringstream str;
    str << buffer;
    Message* msg = serializer->deserealize(&str);

    printf("MESSAGE FROM CLIENT: %s\n", buffer);
}

void SocketTransport::initServ(int clients_number, const char* file, std::map<int, Message*> replies) {
    buffer = new char[BUFFER_SIZE];
    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("socket() failed\n");
        exit(1);
    }

    unlink("./demo_socket");

    /* start with a clean address structure */
    memset(&address, 0, sizeof(struct sockaddr_un));

    address.sun_family = AF_UNIX;
    snprintf(address.sun_path, UNIX_PATH_MAX, "./demo_socket");

    if(bind(socket_fd,
            (struct sockaddr *) &address,
            sizeof(struct sockaddr_un)) != 0)
    {
        printf("bind() failed\n");
        exit(1);
    }

    if(listen(socket_fd, 5) != 0)
    {
        printf("listen() failed\n");
        exit(1);
    }
    connection_fd = accept(socket_fd,
                           (struct sockaddr *) &address,
                           &address_length);
    handle_connection(connection_fd);
    close(connection_fd);
    close(socket_fd);
    unlink("./demo_socket");
}


void SocketTransport::initClient() {
    buffer = new char[BUFFER_SIZE];
    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        perror("socket() failed\n");
        exit (1);
    }

    /* start with a clean address structure */
    memset(&address, 0, sizeof(struct sockaddr_un));

    address.sun_family = AF_UNIX;
    snprintf(address.sun_path, UNIX_PATH_MAX, "./demo_socket");

    if(connect(socket_fd,
               (struct sockaddr *) &address,
               sizeof(struct sockaddr_un)) != 0)
    {
        perror("connect() failed\n");
        exit (1);
    }
}

void SocketTransport::sendMessage(Message* msg) {
    const char *serialized_message;
//    serialized_message = "1234567890";
    std::ostringstream str;
    serializer->serialize(msg, &str);
    serialized_message = str.str().c_str();
    int length = sizeof(serialized_message);
    snprintf(buffer, BUFFER_SIZE, serialized_message);
    write(socket_fd, buffer, BUFFER_SIZE);

    close(socket_fd);
}


