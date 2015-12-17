//
// Created by bolnykh on 12/14/15.
//

#include "BoostSocketTransport.h"
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iomanip>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

using boost::asio::local::stream_protocol;

boost::asio::io_service* io_service_;
stream_protocol::acceptor* acceptor_;
stream_protocol::socket* s;
int request_number;

void BoostSocketTransport::initServ(int clients_number, const char* file, std::map<int, Message*> replies) {
    try
    {
        request_number = clients_number;
        std::remove(file);
        io_service_ = new boost::asio::io_service;
        acceptor_ = new stream_protocol::acceptor(*io_service_, stream_protocol::endpoint(file));
        s = new stream_protocol::socket(*io_service_);

        io_service_->run();
        int requests_received = 0;
        while (requests_received < request_number) {
            acceptor_->accept(*s);
            char* data = readData(s);
            std::stringstream str;
            str << data;
            Message* msg = serializer->deserealize(&str);

            sendMessageInternal(replies[msg->sender_id], s);
            s->close();
            requests_received++;
        }
        io_service_->stop();

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

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

char* BoostSocketTransport::readData(stream_protocol::socket* socket_) {
    // Buffer used to store data received from the client.
    boost::array<char, BoostSocketTransport::BUFFER_SIZE> buffer;
    boost::array<char, 8> header_buffer;

    size_t header_read = boost::asio::read(*socket_, boost::asio::buffer(header_buffer));
    if (header_read < 8) {

    }

    int data_size = atoi(header_buffer.data());
    size_t bytes_read = 0;
    char* temp_array = new char[data_size + 1];
    while (bytes_read < data_size) {
        size_t bytes_iter = socket_->read_some(boost::asio::buffer(buffer));
        for (int i = 0; i < bytes_iter; ++i) {
            temp_array[i + bytes_read] = buffer[i];
        }
        bytes_read += bytes_iter;
    }
    //FUCK YOU C++ WITH YOU FUCKING NULL DELIMETERS
    temp_array[data_size] = '\0';
    return temp_array;
}

void BoostSocketTransport::sendMessage(Message *msg) {
    sendMessageInternal(msg, s);
    char* data = readData(s);
    std::stringstream str;
    str << data;
    Message* mess = serializer->deserealize(&str);
    mess->data;
}

void BoostSocketTransport::sendMessageInternal(Message* msg, stream_protocol::socket* socket) {
    std::stringstream str;
    serializer->serialize(msg, &str);
    str.seekp(0, std::ios::end);
    long size = str.tellp();

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
        str.read(temp_buffer, buf_size);
        buffers.push_back(boost::asio::buffer(temp_buffer, buf_size));
    }

    size_t written = boost::asio::write(*socket, buffers);
}

#else // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
# error Local sockets not available on this platform.
#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
