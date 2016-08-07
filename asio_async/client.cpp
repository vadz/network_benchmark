// Simplest possible asynchronous client using ASIO without TLS.

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

        auto const data = netbench::make_buffer(size);

        netbench::stop_watch sw;

        asio::async_write(
                sock,
                asio::buffer(data),
                [&](error_code ec, size_t length) {
                    if (ec)
                        throw system_error(ec);

                    netbench::print_time_and_speed("Sent", length, sw.msec());

                    io.stop();
                }
            );

        io.run();

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    }
}
