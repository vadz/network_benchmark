// Simplest possible single-threaded server using ASIO with TLS.

#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "netbench/common.hpp"
#include "netbench/server.hpp"
#include "netbench/tls.hpp"

using namespace boost::system;
namespace asio = boost::asio;
using asio::ip::tcp;
using ssl_socket = asio::ssl::stream<tcp::socket>;

class session : public std::enable_shared_from_this<session>
{
public:
    explicit session(ssl_socket& sock) :
        sock_(sock)
    {
    }

    void start()
    {
        do_read();
    }

private:
    void do_read()
    {
        auto self(shared_from_this());

        sock_.async_read_some(
                asio::buffer(data_, sizeof(data_)),
                [this, self](error_code ec, size_t length) {
                    total_ += length;

                    if (ec == asio::error::eof) {
                        netbench::print_time_and_speed(
                                "Received", total_, sw_.msec()
                            );
                        return;
                    }

                    if (ec)
                        throw system_error(ec);

                    do_read();
                }
            );
    }

    ssl_socket& sock_;
    char data_[netbench::SERVER_BUFFER_SIZE];
    size_t total_ = 0;
    netbench::stop_watch sw_;
};

int main(int argc, char* argv[])
{
    try {
        unsigned short port = 0;
        netbench::parse_server_command_line_or_exit(argc, argv, port);

        asio::io_service io;
        auto ctx = netbench::make_server_tls_context();
        tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), port));
        ssl_socket sock(io, ctx);
        acc.accept(sock.lowest_layer());

        sock.handshake(ssl_socket::server);

        std::make_shared<session>(sock)->start();

        io.run();

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    }
}
