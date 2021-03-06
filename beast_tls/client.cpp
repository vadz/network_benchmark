// Simplest possible client using Beast without TLS.

#include <iostream>
#include <sstream>

#include <beast/websocket.hpp>
#include <beast/websocket/ssl.hpp>

#include "netbench/common.hpp"
#include "netbench/client.hpp"
#include "netbench/tls.hpp"

using namespace boost::system;
namespace asio = boost::asio;
using asio::ip::tcp;
using ssl_socket = asio::ssl::stream<tcp::socket>;

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

        auto ctx = netbench::make_client_tls_context();
        ssl_socket sock(io, ctx);

        asio::connect(sock.lowest_layer(), res.resolve(query));
        sock.handshake(ssl_socket::client);

        beast::websocket::stream<ssl_socket&> ws(sock);
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

                ws.close(beast::websocket::close_code::going_away, ec);
                if (ec)
                    throw system_error(ec);

                beast::websocket::opcode op;
                beast::streambuf sb;
                ws.read(op, sb, ec);

                if (ec) {
                    if (ec != beast::websocket::error::closed &&
                            ec != asio::error::eof) {
                        throw system_error(ec);
                    }
                } else {
                    std::cerr << "Ignoring unexpected data after close\n";
                }

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
