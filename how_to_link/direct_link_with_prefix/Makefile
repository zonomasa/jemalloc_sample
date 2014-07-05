TOP = ../..

JE_OPT = prefix

include $(TOP)/mk/common.mk

objs = leak_memory.o
exe  = leak_memory

include $(TOP)/mk/do.mk

run:
	@echo "Run leak_memory by jemalloc"
	HOGE_MALLOC_CONF=$(malloc_conf) ./$(exe)
