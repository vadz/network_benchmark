Benchmark Results
=================

Notice that all speeds are in (mebi) _bytes_ per second and not the, perhaps
more usual, bits per second.

Gigabit LAN Scenario
--------------------

A Windows 7 and a Debian/Wheezy (kernel 3.2.0) machine.

| Windows                      | Linux                        | Speed (MiB/s) |
|------------------------------|------------------------------|---------------|
| iperf -s                     | iperf -c                     |            58 |
| ASIO sync server             | netcat                       |            56 |
| ASIO sync server             | ASIO sync client             |            53 |
