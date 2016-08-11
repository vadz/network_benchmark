# Configurable option, set it to the directory containing Beast headers
# if it's not one of the standard ones.
# BEAST_INCLUDE_DIR :=

ifneq ($(BEAST_INCLUDE_DIR),)
    CPPFLAGS += -I$(BEAST_INCLUDE_DIR)
endif

ifdef USE_MSVC
    # Disable a bunch of warnings about unused parameters and exceeding
    # decorated name length in Beast code.
    CXXFLAGS += /wd4100 /wd4503
endif

# Beast is built on top of Boost.ASIO.
include ../build/boost.make
