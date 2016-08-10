ROOT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))..

# OS-specific part.
OSNAME := $(shell uname -s | cut -d '-' -f 1)
ifeq ($(OSNAME), MINGW32_NT)
    WINDOWS=1
else ifeq ($(OSNAME),CYGWIN_NT)
    CYGWIN=1
    WINDOWS=1
else ifeq ($(OSNAME),Darwin)
    MAC=1
endif

ifdef WINDOWS
    EXE_EXT := .exe
    USE_MSVC := 1
endif

# Compiler-specific stuff.
ifdef USE_MSVC
    CXX := cl /nologo /D_WIN32_WINNT=0x0600 /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_WARNINGS /W4 /MD /EHsc
    OUTPUT_FLAG = /Fd${@:.exe=.pdb}
    LINK_START_FLAG := /link
    LIB_PATH_FLAG := /libpath:
else
    CXXFLAGS += -std=c++11 -pthread
    OUTPUT_FLAG = -o$@
    LIB_PATH_FLAG := -L
endif

# Debugging support.
ifdef DEBUG
    ifdef USE_MSVC
	CXXFLAGS += /Zi
	LDFLAGS += /debug
    else
	CXXFLAGS += -g
    endif
else
    ifdef USE_MSVC
	CXXFLAGS += /O2
    else
	CXXFLAGS += -O2
    endif
endif
