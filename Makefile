sub_dir = bad_usage \
	how_to_link/direct_link \
	how_to_link/direct_link_with_prefix \
	how_to_link/ld_preload


all:subdir
clean:subdir-clean

subdir:
	for dir in $(sub_dir) ; do \
		$(MAKE) -C $$dir JEMALLOC=yes; \
	done

subdir-clean:
	for dir in $(sub_dir) ; do \
		$(MAKE) -C $$dir clean; \
	done
