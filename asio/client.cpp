// Simplest possible single-threaded client using ASIO without TLS.

#include <iomanip>
#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include "netbench/common.hpp"
#include "netbench/client.hpp"

using namespace boost::system;
namespace asio = boost::asio;
using asio::ip::tcp;

int main(int argc, char* argv[])
{
    try {
        std::string host;
        unsigned short port = 0;
        size_t size = 0;
        netbench::parse_client_command_line_or_exit(
                argc, argv, host, port, size
            );

        asio::io_service io;
        tcp::resolver res(io);
        tcp::resolver::query query(tcp::v4(), host, std::to_string(port));
        tcp::socket sock(io);
        asio::connect(sock, res.resolve(query));

        netbench::stop_watch sw;

        asio::write(sock, asio::buffer(netbench::make_buffer(size)));
        sock.close();

        netbench::print_time_and_speed("Sent", size, sw.msec());

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    }
}
