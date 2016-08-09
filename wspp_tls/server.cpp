// Simplest possible WebSocket server using WebSocket++ with TLS.

#include <iostream>

#include <websocketpp/config/asio.hpp>
#include <websocketpp/server.hpp>

#include "netbench/common.hpp"
#include "netbench/server.hpp"
#include "netbench/tls.hpp"

namespace asio = boost::asio;
using server = websocketpp::server<websocketpp::config::asio_tls>;

int main(int argc, char* argv[])
{
    try {
        unsigned short port = 0;
        netbench::parse_server_command_line_or_exit(argc, argv, port);

        netbench::stop_watch sw;
        size_t total = 0;

        server srv;

        // 1GiB should be enough for everybody
        srv.set_max_message_size(1024*1024*1024);
        srv.clear_access_channels(websocketpp::log::alevel::all);
        srv.clear_error_channels(websocketpp::log::elevel::info);
        srv.init_asio();
        srv.set_reuse_addr(true);
        srv.set_tls_init_handler(
            [](websocketpp::connection_hdl) {
                return std::make_shared<netbench::tls_context>(
                        netbench::make_server_tls_context()
                    );
            }
        );
        srv.set_open_handler(
            [&sw](websocketpp::connection_hdl) {
                sw.reset();
            }
        );
        srv.set_message_handler(
            [&total, &srv](
                websocketpp::connection_hdl,
                server::message_ptr msg
            ) {
                total += msg->get_payload().length();
            }
        );
        srv.set_close_handler(
            [&srv](websocketpp::connection_hdl) {
                srv.stop();
            }
        );

        srv.listen(port);
        srv.start_accept();
        srv.run();

        netbench::print_time_and_speed("Received", total, sw.msec());

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    }
}
