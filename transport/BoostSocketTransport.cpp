//
// Created by bolnykh on 12/14/15.
//

#include "BoostSocketTransport.h"
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iomanip>
#include "boost/iostreams/device/array.hpp"
#include "boost/iostreams/stream.hpp"

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

using boost::asio::local::stream_protocol;

boost::asio::io_service* io_service_;
stream_protocol::acceptor* acceptor_;
stream_protocol::socket* s;

void BoostSocketTransport::initServ() {
    try
    {
        std::remove(file);
        io_service_ = new boost::asio::io_service;
        acceptor_ = new stream_protocol::acceptor(*io_service_, stream_protocol::endpoint(file));
        s = new stream_protocol::socket(*io_service_);

        io_service_->run();
    }
    //TODO: Implement correct error handling
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void BoostSocketTransport::initClient() {
    try
    {
        io_service_ = new boost::asio::io_service;;

    }
    //TODO: Implement correct error handling
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void BoostSocketTransport::readData(stream_protocol::socket *socket_, boost::asio::streambuf *buf) {
    // Buffer used to store data received from the client.
    boost::array<char, HEADER_SIZE> header_buffer;

    size_t header_read = boost::asio::read(*socket_, boost::asio::buffer(header_buffer));
    if (header_read < HEADER_SIZE) {

    }

    long data_size = atol(header_buffer.data());
    size_t bytes_read = boost::asio::read(*socket_, buf->prepare(data_size));
    buf->commit(bytes_read);
}

void BoostSocketTransport::sendMessage(Message *msg, std::string destination) {
    sendMessageInternal(msg, s);
}

void BoostSocketTransport::sendMessageInternal(Message* msg, stream_protocol::socket* socket) {
    if (msg == nullptr) {
        return;
    }

    std::stringstream str;
    serializer->serialize(msg, &str);
    str.seekp(0, std::ios::end);
    long size = str.tellp();

    str.seekp(0, std::ios::beg);
    std::ostringstream header_stream;
    header_stream << std::setw(HEADER_SIZE)
    << std::hex << std::to_string(size).c_str();

    std::string size_str = std::to_string(size);
    std::array<char, HEADER_SIZE> head_buf;
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

int BoostSocketTransport::connectAddress(std::string address) {
    bool connected = false;
    s = new stream_protocol::socket(*io_service_);
    while (!connected) {
        try {
            s->connect(stream_protocol::endpoint(address));
            connected = true;
        }
        catch (std::exception& e) {
            continue;
        }
    }
    return 0;
}

Message * BoostSocketTransport::receiveMessage(std::string source) {
    boost::asio::streambuf sb;
    readData(s, &sb);

    std::istream is(&sb);
    Message* msg = serializer->deserealize(&is);
    return msg;
}

void BoostSocketTransport::closeConnection() {
    s->close();
    io_service_->stop();
}

int BoostSocketTransport::acceptConnection(std::string address) {
    acceptor_->accept(*s);
    return 0;
}
