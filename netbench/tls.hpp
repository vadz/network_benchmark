// Helpers for servers using TLS.
#ifndef network_benchmarks_tls_hpp_
#define network_benchmarks_tls_hpp_

#include "netbench/dhparams.h"

namespace netbench
{

namespace asio = boost::asio;
using tls_context = asio::ssl::context;

inline tls_context
make_client_tls_context()
{
    auto ctx = tls_context(tls_context::tlsv12);

    ctx.set_options(
        tls_context::default_workarounds |
        tls_context::no_sslv2 |
        tls_context::no_sslv3 |
        tls_context::no_tlsv1 |
        tls_context::single_dh_use
    );

    return ctx;
}

inline tls_context
make_server_tls_context()
{
    auto ctx = make_client_tls_context();
    ctx.use_certificate_chain_file("snakeoil.crt");
    ctx.use_private_key_file("snakeoil.key", tls_context::pem);
    ctx.use_tmp_dh(asio::const_buffer(dhparams_data, dhparams_len));

    return ctx;
}

} // namespace netbench

#endif // network_benchmarks_tls_hpp_

