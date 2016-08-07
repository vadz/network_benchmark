// Common helpers for all clients implementations.
#ifndef network_benchmarks_client_h_
#define network_benchmarks_client_h_

#include <string>

namespace netbench
{

// Parse command line, return the host name, port number and buffer size
// specified on it or exit if it doesn't have the correct syntax.
inline void
parse_client_command_line_or_exit(
        int argc, char* argv[],
        std::string& host, unsigned short& port, size_t& size
    )
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <host> <port> <transfer-size>\n";
        std::exit(1);
    }

    host = argv[1];
    port = parse_port_or_exit(argv[2]);
    auto const llsize = std::atoll(argv[3]);
    if (llsize <= 0) {
        std::cerr << "\"" << argv[3] << "\" is not a valid transfer size\n";
        std::exit(1);
    }
    size = static_cast<size_t>(llsize);
}

// Create a buffer of the given size filled with some data.
std::string make_buffer(size_t size)
{
    std::string s(size, '\0');
    for (size_t n = 0; n < size; ++n) {
        s[n] = 'A' + n % 26;
    }

    return s;
}

} // namespace netbench

#endif // network_benchmarks_client_h_
