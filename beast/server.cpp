// Simplest possible server using Beast without TLS.

#include <iostream>

#include <beast/websocket.hpp>

#include "netbench/common.hpp"
#include "netbench/server.hpp"

using namespace boost::system;
namespace asio = boost::asio;
using asio::ip::tcp;

using wsstream = beast::websocket::stream<tcp::socket&>;

class session : public std::enable_shared_from_this<session>
{
public:
    explicit session(wsstream& ws) :
        ws_(ws)
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

        ws_.async_read(
            op_,
            sb_,
            [this, self](error_code ec) {
                if (ec == beast::websocket::error::closed) {
                    netbench::print_time_and_speed(
                            "Received", total_, sw_.msec()
                        );
                    return;
                }

                if (ec)
                    throw system_error(ec);

                auto const recv = sb_.size();
                total_ += recv;
                sb_.consume(recv);

                do_read();
            }
        );
    }

    wsstream& ws_;
    beast::websocket::opcode op_;
    beast::streambuf sb_;
    size_t total_ = 0;
    netbench::stop_watch sw_;
};

int main(int argc, char* argv[])
{
    try {
        unsigned short port = 0;
        netbench::parse_server_command_line_or_exit(argc, argv, port);

        asio::io_service io;
        tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), port));
        tcp::socket sock(io);
        acc.accept(sock);

        wsstream ws(sock);
        ws.set_option(beast::websocket::read_message_max(1024*1024*1024));
        ws.accept();

        std::make_shared<session>(ws)->start();

        io.run();

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    }
}
