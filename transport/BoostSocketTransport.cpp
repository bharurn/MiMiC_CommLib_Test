//
// Created by bolnykh on 12/14/15.
//

#include "BoostSocketTransport.h"
#include <cstdio>
#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <iomanip>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

using boost::asio::local::stream_protocol;

class session
        : public boost::enable_shared_from_this<session>
{
public:
    session(boost::asio::io_service& io_service)
            : socket_(io_service)
    {
    }

    stream_protocol::socket& socket()
    {
        return socket_;
    }

    char* start()
    {
        //read header
        size_t header_read = boost::asio::read(socket_, boost::asio::buffer(header_buffer));
        if (header_read < 8) {

        }

        int data_size = atoi(header_buffer.data());
        size_t bytes_read = 0;
        boost::system::error_code error;
        char* temp_array = new char[data_size + 1];
        while (bytes_read < data_size) {
//            size_t bytes_iter = boost::asio::read(socket_, boost::asio::buffer(buffer));
            size_t bytes_iter = socket_.read_some(boost::asio::buffer(buffer));
            for (int i = 0; i < bytes_iter; ++i) {
                temp_array[i + bytes_read] = buffer[i];
            }
            bytes_read += bytes_iter;
        }
        //FUCK YOU C++ WITH YOU FUCKING NULL DELIMETERS
        temp_array[data_size] = '\0';
        socket_.close();
        return temp_array;
    }

private:
    // The socket used to communicate with the client.
    stream_protocol::socket socket_;

    // Buffer used to store data received from the client.
    boost::array<char, BoostSocketTransport::BUFFER_SIZE> buffer;
    boost::array<char, 8> header_buffer;
    char* data;
    std::vector<std::string>* temp;
};

typedef boost::shared_ptr<session> session_ptr;

class server
{
public:
    server(boost::asio::io_service& io_service, const std::string& file, Serializer* serializer)
            : io_service_(io_service),
              acceptor_(io_service, stream_protocol::endpoint(file)),
              serializer(serializer)
    {
        session_ptr new_session(new session(io_service_));
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(session_ptr new_session,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            char* result = new_session->start();
            std::stringstream str;
            str << result;
            Message* msg = serializer->deserealize(&str);
            msg->data;
        }

        new_session.reset(new session(io_service_));
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

private:
    boost::asio::io_service& io_service_;
    stream_protocol::acceptor acceptor_;
    Serializer* serializer;
};


void BoostSocketTransport::initServ() {
    try
    {
        boost::asio::io_service io_service;

        std::remove("./demo_socket");
        server s(io_service, "./demo_socket", serializer);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

stream_protocol::socket* s;
void BoostSocketTransport::initClient() {
    try
    {
        boost::asio::io_service io_service;
        s = new stream_protocol::socket(io_service);
        s->connect(stream_protocol::endpoint("./demo_socket"));

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void BoostSocketTransport::sendMessage(Message *msg) {
    std::stringstream str;
    serializer->serialize(msg, &str);
    str.seekp(0, std::ios::end);
    long size = str.tellp();
//    str << '\0';

    str.seekp(0, std::ios::beg);
    std::ostringstream header_stream;
    header_stream << std::setw(8)
    << std::hex << std::to_string(size).c_str();

    std::string size_str = std::to_string(size);
    std::array<char, 8> head_buf;
    std::copy(size_str.begin(), size_str.end(), head_buf.data());

    int buffer_number = 1 + size / BUFFER_SIZE;

    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(head_buf));
    for (int i = 0; i < buffer_number; ++i) {
        long temp_size = size - BUFFER_SIZE * i;
        long temp = BUFFER_SIZE;
        long buf_size = std::min(temp, temp_size);
        char* temp_buffer = new char[buf_size];
        std::vector<char> buffer;
//        std::array chars = new std::array(temp_buffer);
        str.read(temp_buffer, buf_size);
        buffers.push_back(boost::asio::buffer(temp_buffer, buf_size));
    }
//    buffers.push_back(boost::asio::buffer(str, size));

    size_t written = boost::asio::write(*s, buffers);
    if (written < 8) {

    }
    size_t sent_bytes;
//    do {
//        sent_bytes = s->write_some(boost::asio::buffer(str, size));
//    }
//    while(sent_bytes < size);

    //FIXME: THIS WORKS
//    stream << header_stream.str();
//    stream << str.str();
//    stream << '\0';

//        stream.flush();
//    Message* mes = serializer->deserealize(&stream);
//    std::string line;
//    std::vector<std::string> lines;
//    std::getline(stream, line);
//    while (!line.empty()) {
//        std::getline(stream, line);
//        lines.push_back(line);
//    }
//    std::cout << line << "\n";
//    stream.close();
//    using namespace std; // For strlen.
//    char* request[BUFFER_SIZE];
//
//    size_t request_length = BUFFER_SIZE;
//    const char *serialized_message;
////    serialized_message = "1234567890";
//    std::ostringstream str;
//    serializer->serialize(msg, &str);
//    serialized_message = str.str().c_str();
//    boost::asio::write(stream, boost::asio::buffer(request, request_length));
//
//    char reply[BUFFER_SIZE];
//    size_t reply_length = boost::asio::read(stream,
//                                            boost::asio::buffer(reply, request_length));
//    std::cout << "Reply is: ";
//    std::cout.write(reply, reply_length);
//    std::cout << "\n";
}

#else // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
# error Local sockets not available on this platform.
#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
