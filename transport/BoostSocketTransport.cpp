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

    void start()
    {
//        socket_.async_read_some(boost::asio::buffer(buffer),
//                                boost::bind(&session::handle_read,
//                                            shared_from_this(),
//                                            boost::asio::placeholders::error,
//                                            boost::asio::placeholders::bytes_transferred));
        size_t num_bytes = 1;
        boost::system::error_code error;
        while (num_bytes > 0) {
            try {
                num_bytes = boost::asio::read(socket_, boost::asio::buffer(buffer));
//            num_bytes = socket_.read_some(boost::asio::buffer(buffer), error);
                temp.push_back(buffer.data());
            }
            catch (boost::system::system_error& e) {
                std::cerr << "Exception: " << e.what() << "\n";
            }
        }
        socket_.close();

//        boost::asio::async_write(socket_,
//                                 boost::asio::buffer(buffer, 10),
//                                 boost::bind(&session::handle_write,
//                                             shared_from_this(),
//                                             boost::asio::placeholders::error));
    }

    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred)
    {
        if (!error)
        {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(buffer, bytes_transferred),
                                     boost::bind(&session::handle_write,
                                                 shared_from_this(),
                                                 boost::asio::placeholders::error));
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)
        {
            socket_.async_read_some(boost::asio::buffer(buffer),
                                    boost::bind(&session::handle_read,
                                                shared_from_this(),
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
        }
    }

private:
    // The socket used to communicate with the client.
    stream_protocol::socket socket_;

    // Buffer used to store data received from the client.
    boost::array<char, 10> buffer;
    char* data;
    std::vector<std::string> temp;
};

typedef boost::shared_ptr<session> session_ptr;

class server
{
public:
    server(boost::asio::io_service& io_service, const std::string& file)
            : io_service_(io_service),
              acceptor_(io_service, stream_protocol::endpoint(file))
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
            new_session->start();
        }

        new_session.reset(new session(io_service_));
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

private:
    boost::asio::io_service& io_service_;
    stream_protocol::acceptor acceptor_;
};


void BoostSocketTransport::initServ() {
    try
    {
        boost::asio::io_service io_service;

        std::remove("./demo_socket");
        server s(io_service, "./demo_socket");

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

boost::asio::local::stream_protocol::iostream stream;
void BoostSocketTransport::initClient() {
    try
    {
        int max_length = 10;
//        boost::asio::io_service io_service;
        std::string data = "1,2,3,4,5,6,7,8,9,10";
        char buffer[max_length];
        stream.connect(stream_protocol::endpoint("./demo_socket"));
        std::ostringstream header_stream;
        header_stream << std::setw(8)
        << std::hex << data.size();
        stream << header_stream.c_str
        stream << data;

//        stream.flush();
        std::string line;
        std::getline(stream, line);
        std::cout << line << "\n";
        stream.close();

        boost::asio::io_service io_service;

        stream_protocol::socket s(io_service);
        s.connect(stream_protocol::endpoint("./demo_socket"));

        using namespace std; // For strlen.
        std::cout << "Enter message: ";
        char request[max_length];
        std::cin.getline(request, max_length);
        size_t request_length = strlen(request);
        boost::asio::write(s, boost::asio::buffer(request, request_length));

        char reply[max_length];
        size_t reply_length = boost::asio::read(s,
                                                boost::asio::buffer(reply, request_length));
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void BoostSocketTransport::sendMessage(Message *msg) {
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
