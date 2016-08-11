SUBDIRS := asio asio_async asio_async_tls asio_tls beast beast_tls wspp wspp_tls

all: $(foreach d,$(SUBDIRS),$d.build)

$(foreach d,$(SUBDIRS),$d.build):
	$(MAKE) -C ${@:.build=}

clean: $(foreach d,$(SUBDIRS),$d.clean)

$(foreach d,$(SUBDIRS),$d.clean):
	$(MAKE) -C ${@:.clean=} clean

.PHONY: all clean $(foreach d,$(SUBDIRS),$d.build $d.clean)
