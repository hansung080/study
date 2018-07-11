# Makefile

SRCS=count_thread.c count_thread_mutex.c calc_multi_cond.c
OBJS=count_thread.o count_thread_mutex.o calc_multi_cond.o
TARGET1=count-thread
TARGET2=count-thread-mutex
TARGET3=calc-multi-cond
CC=gcc

all: dep $(TARGET1) $(TARGET2) $(TARGET3)

dep:
	$(CC) -MM $(SRCS) > Dependency.dep

$(OBJS): $(SRCS)
	$(CC) -c $^ -pthread

$(TARGET1): count_thread.o
	$(CC) -o $@ $^ -lpthread

$(TARGET2): count_thread_mutex.o
	$(CC) -o $@ $^ -lpthread

$(TARGET3): calc_multi_cond.o
	$(CC) -o $@ $^ -lpthread

clean:
	rm -f Dependency.dep
	rm -f *.pch
	rm -f *.gch
	rm -f *.stackdump
	rm -f *.o
	rm -f $(TARGET1)
	rm -f $(TARGET2)
	rm -f $(TARGET3)
	
ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif

