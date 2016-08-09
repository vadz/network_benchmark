# Configurable options, set them if OpenSSL headers/libraries are not found by
# the compiler/linker in the default locations.
OPENSSL_INCLUDE_DIR :=
OPENSSL_LIB_DIR :=

ifdef WINDOWS
    LIBS += libeay32.lib ssleay32.lib
else
    LIBS += -lssl -lcrypto
endif

ifneq ($(OPENSSL_INCLUDE_DIR),)
    CPPFLAGS += -I$(OPENSSL_INCLUDE_DIR)
endif
ifneq ($(OPENSSL_LIB_DIR),)
    LIBS := $(LIB_PATH_FLAG)$(OPENSSL_LIB_DIR) $(LIBS)
endif

# This is used as a dependency in rules.make
TLS_HEADER := $(ROOT_DIR)/netbench/tls.hpp
