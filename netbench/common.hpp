// Common helpers for both servers and clients.
#ifndef network_benchmarks_common_h_
#define network_benchmarks_common_h_

#include <chrono>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>

namespace netbench
{

using milliseconds = std::chrono::milliseconds;

// Simplest possible stopwatch class allowing to measure the time taken by some
// code.
class stop_watch
{
public:
    using clock = std::chrono::high_resolution_clock;

    stop_watch()
    {
        reset();
    }

    void reset()
    {
        start_ = clock::now();
    }

    milliseconds msec() const
    {
        return std::chrono::duration_cast<milliseconds>(clock::now() - start_);
    }

private:
    clock::time_point start_;
};

// Show the time taken to transfer the given amount of bytes and the speed
// computed from it.
inline void
print_time_and_speed(char const* verb, size_t total, milliseconds ms)
{
    std::cout << verb << " " << total << " bytes in " << ms.count() << "ms ("
              << std::setiosflags(std::ios_base::fixed)
              << std::setprecision(1)
              << (static_cast<float>(total)*1000 / (1024*1024*ms.count()))
              << " MiB/s)\n";
}

// Parse the port specified by the given string and exit if it's invalid.
unsigned short
parse_port_or_exit(char const* s)
{
    auto const port = std::atoi(s);
    if (port <= 0 || port > USHRT_MAX) {
        std::cerr << "\"" << s << "\" is not a valid port number\n";
        std::exit(1);
    }

    return static_cast<unsigned short>(port);
}

} // namespace netbench

#endif // network_benchmarks_common_h_
