CC      = g++
LINK    = g++

ifeq ($(JEMALLOC),no)
  CFLAGS  = -g -Wall -Wextra
  LDLIBS  =
else
  JE_OPT ?= prof            # defualt is prof
  ifeq ($(JE_OPT),debug)
    JE_DIR = debug
  else
    ifeq ($(JE_OPT),prefix)
      JE_DIR = prefix
    else
      ifeq ($(JE_OPT),prof)
        JE_DIR = prof
      else
        JE_DIR = rel
      endif
    endif
  endif
  CFLAGS  = -g -Wall -Wextra -DUSE_JEMALLOC -I$(TOP)/include/$(JE_DIR)
  LDLIBS  = -Wl,-rpath,$(TOP)/lib/$(JE_DIR) -L$(TOP)/lib/$(JE_DIR) -ljemalloc

  ifeq ($(STATS_PRINT),yes)
    CFLAGS  += -DSTATS_PRINT -I$(TOP)/include/$(JE_DIR)
  endif

  malloc_conf = "prof_leak:true,lg_prof_sample:1"
endif

