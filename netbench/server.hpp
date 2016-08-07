// Common helpers for all server implementations.
#ifndef network_benchmarks_server_h_
#define network_benchmarks_server_h_

namespace netbench
{

// Receiving buffer size.
const size_t SERVER_BUFFER_SIZE = 65*1024;

// Parse command line, return the port number specified on it or exit if it
// doesn't have the correct syntax.
inline void
parse_server_command_line_or_exit(int argc, char* argv[], unsigned short& port)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        std::exit(1);
    }

    port = parse_port_or_exit(argv[1]);
}

} // namespace netbench

#endif // network_benchmarks_server_h_
