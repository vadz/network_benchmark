# Configurable option, set it to the directory containing WebSocket++ headers
# if it's not one of the standard ones.
# WSPP_INCLUDE_DIR :=

ifneq ($(WSPP_INCLUDE_DIR),)
    CPPFLAGS += -I$(WSPP_INCLUDE_DIR)
endif

ifdef USE_MSVC
    # Disable (harmless) warning about "while(1)" in WebSocket++ code.
    CXXFLAGS += /wd4127
endif

# WebSocket++ is built on top of Boost.ASIO.
include ../build/boost.make
