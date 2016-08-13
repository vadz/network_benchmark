Benchmark Results
=================

Notice that all speeds are in (mebi) _bytes_ per second and not the, perhaps
more usual, bits per second.

`iperf` below stands for `iperf -s` on the server (without any additional
tuning) and `iperf -c <host> -n 100M` on the client. All client runs also used
100M transfer size (104857600 bytes) and in all cases the median of 5 runs was
taken.

Gigabit LAN Scenario
--------------------

A Windows 7 and a Debian/Wheezy (kernel 3.2.0) machine.

### Windows client/Linux server

| Client                       | Server                       | Speed (MiB/s) |
|------------------------------|------------------------------|---------------|
| iperf                        | iperf                        |          54.0 |
| ASIO sync                    | ASIO sync                    |          49.2 |
| ASIO sync TLS                | ASIO sync TLS                |          45.1 |
| ASIO sync                    | ASIO async                   |          49.0 |
| ASIO async                   | ASIO sync                    |          48.4 |
| ASIO async                   | ASIO async                   |          54.0 |
| ASIO async TLS               | ASIO async TLS               |          51.5 |
| WSPP                         | WSPP                         |          46.7 |
| WSPP TLS                     | WSPP TLS                     |          40.8 |
| WSPP                         | Beast                        |          46.9 |
| Beast                        | Beast                        |          41.8 |
| WSPP TLS                     | Beast TLS                    |          40.1 |
| Beast TLS                    | Beast TLS                    |          35.7 |
| Beast TLS                    | WSPP TLS                     |          38.0 |

### Windows server/Linux client

| Client                       | Server                       | Speed (MiB/s) |
|------------------------------|------------------------------|---------------|
| iperf                        | iperf                        |          55.8 |
| ASIO sync                    | ASIO sync                    |          46.9 |
| ASIO sync TLS                | ASIO sync TLS                |          47.3 |
| ASIO sync                    | ASIO async                   |          46.6 |
| ASIO async                   | ASIO sync                    |          48.9 |
| ASIO async                   | ASIO async                   |          51.1 |
| ASIO async TLS               | ASIO async TLS               |          49.5 |
| WSPP                         | WSPP                         |          47.1 |
| WSPP TLS                     | WSPP TLS                     |          47.6 |
| WSPP                         | Beast                        |          47.0 |
| Beast                        | Beast                        |          50.5 |
| Beast TLS                    | WSPP TLS                     |          51.3 |
| Beast TLS                    | Beast TLS                    |          51.3 |
