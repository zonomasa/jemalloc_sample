TOP = ../..

include $(TOP)/mk/common.mk

objs = leak_memory.o
exe  = leak_memory

include $(TOP)/mk/do.mk

run:
	@echo "Run leak_memory by jemalloc"
	MALLOC_CONF=$(malloc_conf) ./$(exe)
