// Common helpers for all server implementations.
#ifndef network_benchmarks_server_h_
#define network_benchmarks_server_h_

#include <climits>
#include <cstdlib>

namespace netbench
{

// Receiving buffer size.
const size_t SERVER_BUFFER_SIZE = 65*1024;

// Parse command line, return the port number specified on it or exit if it
// doesn't have the correct syntax.
unsigned short get_port_from_command_line_or_exit(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        std::exit(1);
    }

    auto const port = std::atoi(argv[1]);
    if (port <= 0 || port > USHRT_MAX) {
        std::cerr << "\"" << argv[1] << "\" is not a valid port number\n";
        std::exit(1);
    }

    return static_cast<unsigned short>(port);
}

} // namespace netbench

#endif // network_benchmarks_server_h_
