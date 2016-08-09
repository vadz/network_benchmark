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

        netbench::stop_watch sw;

        size_t total = 0;
        char data[netbench::SERVER_BUFFER_SIZE];
        for (;;) {
            error_code ec;
            total += sock.read_some(asio::buffer(data), ec);
            if (ec == asio::error::eof)
                break;
            if (ec)
                throw system_error(ec);
        }

        netbench::print_time_and_speed("Received", total, sw.msec());

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    }
}
