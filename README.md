Network Libraries Benchmarks for C++
====================================

This repository contains several simple benchmarks comparing performance of
various network libraries and protocols with and without TLS.

All benchmarks consist of a client and server pair, with the client sending a
buffer of the given size to the server and waiting to receive an
acknowledgement from the server, then exiting.

Building
--------

Very simple GNU make makefiles are provided for building and can be used in
each subdirectory as

	$ make -C asio

These can be used under Windows too in a Cygwin environment (MSYS could work
but wasn't tested). Notice that under Windows Microsoft Visual C++ is used, so
the appropriate environment variables need to be set (usually this is achieved
by running Cygwin shell from a cmd.exe launched via "Developer Command Prompt
for VS20xx" shortcut).

Also, if the required headers or libraries are not available in the default
locations searched by the compiler/linker, the `XXX_INCLUDE_DIR` and
`XXX_LIB_DIR` variables need to be defined to point to them, e.g.

	$ make -C asio BOOST_INCLUDE_DIR=$HOME/include BOOST_LIB_DIR=$HOME/lib

Certificates
------------

By default self-signed certificate from this repository itself is used for
TLS-enabled benchmarks, feel free to replace it with any other one. For the
record, this certificate was created using the following command:

	$ openssl req -newkey rsa:2048 -nodes -keyout snakeoil.priv -x509 -days 3655 -out snakeoil.pem -subj "/C=FR/L=Paris/O=Network benchmarks/CN=netbench.tt-solutions.com"
