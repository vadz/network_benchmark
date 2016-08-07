// Simplest possible single-threaded server using ASIO with TLS.

#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "netbench/common.hpp"
#include "netbench/dhparams.h"
#include "netbench/server.hpp"

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

        asio::ssl::context ctx(asio::ssl::context::tlsv12);
        ctx.set_options(
                boost::asio::ssl::context::default_workarounds |
                boost::asio::ssl::context::no_sslv2 |
                boost::asio::ssl::context::no_sslv3 |
                boost::asio::ssl::context::no_tlsv1 |
                boost::asio::ssl::context::single_dh_use
            );
        ctx.use_certificate_chain_file("snakeoil.crt");
        ctx.use_private_key_file("snakeoil.key", asio::ssl::context::pem);
        ctx.use_tmp_dh(boost::asio::const_buffer(dhparams_data, dhparams_len));

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
