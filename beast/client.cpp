// Simplest possible client using Beast without TLS.

#include <iostream>
#include <sstream>

#include <beast/websocket.hpp>

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

        std::ostringstream uri;
        uri << "ws://" << host << ":" << port;

        asio::io_service io;
        tcp::resolver res(io);
        tcp::resolver::query query(tcp::v4(), host, std::to_string(port));
        tcp::socket sock(io);
        asio::connect(sock, res.resolve(query));

        beast::websocket::stream<tcp::socket&> ws(sock);
        ws.handshake(uri.str(), "/");

        ws.set_option(beast::websocket::message_type{beast::websocket::opcode::binary});
        ws.set_option(beast::websocket::auto_fragment_size{0});

        auto const data = netbench::make_buffer(size);

        netbench::stop_watch sw;

        ws.async_write(
            asio::buffer(data),
            [&](error_code ec) {
                if (ec)
                    throw system_error(ec);

                netbench::print_time_and_speed("Sent", size, sw.msec());

                ws.async_close(
                    beast::websocket::close_code::going_away,
                    [&io](error_code ec) {
                        io.stop();
                    }
                );
            }
        );

        io.run();

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    }
}
