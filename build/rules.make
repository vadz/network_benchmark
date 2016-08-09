server := server$(EXE_EXT)
client := client$(EXE_EXT)

all: $(server) $(client)

# Generic rules for the server and client programs.
$(server): server.cpp $(ROOT_DIR)/netbench/common.hpp $(ROOT_DIR)/netbench/server.hpp $(TLS_HEADER)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOT_DIR) $(call OUTPUT_FLAG) $< $(LINK_START_FLAG) $(LDFLAGS) $(LIBS)

$(client): client.cpp $(ROOT_DIR)/netbench/common.hpp $(ROOT_DIR)/netbench/client.hpp $(TLS_HEADER)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOT_DIR) $(call OUTPUT_FLAG) $< $(LINK_START_FLAG) $(LDFLAGS) $(LIBS)

clean:
	$(RM) $(wildcard server$(EXE_EXT)) $(wildcard client$(EXE_EXT))
ifdef WINDOWS
	$(RM) $(wildcard *.obj) $(wildcard *.pdb)
endif
