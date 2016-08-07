// Simplest possible single-threaded server using ASIO without TLS.

#include <iostream>

#include <boost/asio.hpp>

#include "netbench/common.hpp"
#include "netbench/server.hpp"

using namespace boost::system;
namespace asio = boost::asio;
using asio::ip::tcp;

int main(int argc, char* argv[])
{
    try {
        auto const
            port = netbench::get_port_from_command_line_or_exit(argc, argv);

        asio::io_service io;
        tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), port));
        tcp::socket sock(io);
        acc.accept(sock);

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
