// Common helpers for both servers and clients.
#ifndef network_benchmarks_common_h_
#define network_benchmarks_common_h_

#include <chrono>

namespace netbench
{

// Simplest possible stopwatch class allowing to measure the time taken by some
// code.
class stop_watch
{
public:
    using clock = std::chrono::high_resolution_clock;

    stop_watch() :
        start_(clock::now())
    {
    }

    long long msec() const
    {
        auto const d = clock::now() - start_;
        return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
    }

private:
    clock::time_point start_;
};

} // namespace netbench

#endif // network_benchmarks_common_h_
