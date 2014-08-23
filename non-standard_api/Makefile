TOP = ..

include $(TOP)/mk/common.mk

objs = non-standard_api.o
exe  = non-standard_api.exe

include $(TOP)/mk/do.mk

jemalloc_path = $(TOP)/lib/prof/libjemalloc.so
jemalloc_path_debug = $(TOP)/lib/debug/libjemalloc.so

run:
	./$(exe)


### double-free ###
#	MALLOC_CONF="tcache:false" LD_PRELOAD=$(jemalloc_path_debug) ./$(exe)

### leak ###
#	MALLOC_CONF="prof_leak:true,lg_prof_sample:1" LD_PRELOAD=$(jemalloc_path) ./$(exe)

### redzone ###
#	MALLOC_CONF="redzone:true,junk:true" LD_PRELOAD=$(jemalloc_path) ./$(exe)

### full ###
#	MALLOC_CONF="redzone:true,junk:true,tcache:false,prof_leak:true,prof:true,lg_prof_sample:1,prof_accum:false,prof_prefix:jeprof.out" LD_PRELOAD=$(jemalloc_path) ./$(exe)
