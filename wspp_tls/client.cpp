// Simplest possible single-threaded client using WebSocket++ with TLS.

#include <iostream>
#include <sstream>

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include "netbench/common.hpp"
#include "netbench/client.hpp"
#include "netbench/tls.hpp"

namespace asio = boost::asio;
using client = websocketpp::client<websocketpp::config::asio_tls_client>;

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
        uri << "wss://" << host << ":" << port;

        client c;
        c.set_max_message_size(1024*1024*1024);
        c.clear_access_channels(websocketpp::log::alevel::all);
        c.init_asio();

        auto const data = netbench::make_buffer(size);

        netbench::stop_watch sw;

        c.set_tls_init_handler(
            [=](websocketpp::connection_hdl hdl) {
                return std::make_shared<netbench::tls_context>(
                        netbench::make_client_tls_context()
                    );
            }
        );
        c.set_open_handler(
            [=, &c, &sw](websocketpp::connection_hdl hdl) {
                sw.reset();
                c.send(hdl, data, websocketpp::frame::opcode::binary);
                c.close(hdl, websocketpp::close::status::going_away, "");
            }
        );
        c.set_close_handler(
            [=, &c, &sw](websocketpp::connection_hdl hdl) {
                netbench::print_time_and_speed("Sent", size, sw.msec());
            }
        );

        websocketpp::lib::error_code ec;
        client::connection_ptr conn = c.get_connection(uri.str(), ec);
        if (ec)
            throw websocketpp::exception(ec);
        c.connect(conn);
        c.run();

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    }
}
