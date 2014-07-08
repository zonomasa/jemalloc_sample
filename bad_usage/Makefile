TOP = ..

include $(TOP)/mk/common.mk

objs = error_memory.o
exe  = error_memory

include $(TOP)/mk/do.mk

jemalloc_path = $(TOP)/lib/prof/libjemalloc.so
jemalloc_path_debug = $(TOP)/lib/debug/libjemalloc.so


run:
	@echo ""
	@echo "========================================================================="
	@echo "./bad_usage"
	@echo "========================================================================="
	@echo "-------------------------------------------------------------------------"
	@echo "Run with glibc malloc"
	@echo "-------------------------------------------------------------------------"
	./$(exe)
	@echo ""
	@echo "-------------------------------------------------------------------------"
	@echo "Jemalloc(redzone)"
	@echo "-------------------------------------------------------------------------"
	MALLOC_CONF="redzone:true,junk:true" LD_PRELOAD=$(jemalloc_path) ./$(exe)
	@echo ""
	@echo "-------------------------------------------------------------------------"
	@echo "Jemalloc(leak)"
	@echo "-------------------------------------------------------------------------"
	MALLOC_CONF="prof_leak:true,lg_prof_sample:1" LD_PRELOAD=$(jemalloc_path) ./$(exe)
	@echo "-------------------------------------------------------------------------"
	@echo "Jemalloc(double-free)"
	@echo "-------------------------------------------------------------------------"
	MALLOC_CONF="tcache:false" LD_PRELOAD=$(jemalloc_path_debug) ./$(exe)
#	MALLOC_CONF="prof_leak:true,lg_prof_sample:1" LD_PRELOAD=$(jemalloc_path_debug) ./$(exe)



### full ###
#	MALLOC_CONF="redzone:true,junk:true,tcache:false,prof_leak:true,prof:true,lg_prof_sample:1,prof_accum:false,prof_prefix:jeprof.out" LD_PRELOAD=$(jemalloc_path) ./$(exe)
