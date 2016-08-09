SUBDIRS := asio asio_async asio_tls wspp

all: $(foreach d,$(SUBDIRS),$d.build)

$(foreach d,$(SUBDIRS),$d.build):
	$(MAKE) -C ${@:.build=}

clean: $(foreach d,$(SUBDIRS),$d.clean)

$(foreach d,$(SUBDIRS),$d.clean):
	$(MAKE) -C ${@:.clean=} clean

.PHONY: all clean $(foreach d,$(SUBDIRS),$d.build $d.clean)
