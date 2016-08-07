# Configurable options, set them if Boost headers/libraries (only boost_system
# is really needed) are not found by the compiler/linker in the default
# locations.
BOOST_INCLUDE_DIR :=
BOOST_LIB_DIR :=

# Don't automatically link with the corresponding libraries with MSVC, we
# don't really need them.
ifdef WINDOWS
    CPPFLAGS += -DBOOST_REGEX_NO_LIB -DBOOST_DATE_TIME_NO_LIB
endif

ifneq ($(BOOST_INCLUDE_DIR),)
    CPPFLAGS += -I$(BOOST_INCLUDE_DIR)
endif

# Rely on auto-linking the correctly named library when using MSVC.
ifndef WINDOWS
    LIBS += -lboost_system
endif

ifneq ($(BOOST_LIB_DIR),)
    LIBS := $(LIB_PATH_FLAG)$(BOOST_LIB_DIR) $(LIBS)
endif
