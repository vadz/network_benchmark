# Configurable options, set them if zlib headers/libraries are not found by
# the compiler/linker in the default locations.
# ZLIB_INCLUDE_DIR :=
# ZLIB_LIB_DIR :=

ifdef WINDOWS
    LIBS += zlib.lib
else
    LIBS += -lz
endif

ifneq ($(ZLIB_INCLUDE_DIR),)
    CPPFLAGS += -I$(ZLIB_INCLUDE_DIR)
endif
ifneq ($(ZLIB_LIB_DIR),)
    LIBS := $(LIB_PATH_FLAG)$(ZLIB_LIB_DIR) $(LIBS)
endif
