# Configurable option, set it to the directory containing WebSocket++ headers
# if it's not one of the standard ones.
WSPP_INCLUDE_DIR :=

ifneq ($(WSPP_INCLUDE_DIR),)
    CPPFLAGS += -I$(WSPP_INCLUDE_DIR)
endif

# WebSocket++ is built on top of Boost.ASIO.
include ../build/boost.make
