TOP = ../..

include $(TOP)/mk/common.mk

objs = leak_memory.o
exe  = leak_memory

include $(TOP)/mk/do.mk

jemalloc_path = $(TOP)/lib/prof/libjemalloc.so
malloc_conf = "prof_leak:true,lg_prof_sample:1"

run:
	@echo "Run leak_memory" 
	./$(exe)
	@echo "Run leak_memory by jemalloc"
	MALLOC_CONF=$(malloc_conf) LD_PRELOAD=$(jemalloc_path) ./$(exe)
