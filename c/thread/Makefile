# Makefile

SRCS=count_thread.c count_thread_mutex.c
OBJS=count_thread.o count_thread_mutex.o
TARGET1=count-thread
TARGET2=count-thread-mutex
CC=gcc

all: dep $(TARGET1) $(TARGET2)

dep:
	$(CC) -MM $(SRCS) > Dependency.dep

$(OBJS): $(SRCS)
	$(CC) -c $^

$(TARGET1): count_thread.o
	$(CC) -o $@ $^ -lpthread

$(TARGET2): count_thread_mutex.o
	$(CC) -o $@ $^ -lpthread

clean:
	rm -f Dependency.dep
	rm -f *.pch
	rm -f *.gch
	rm -f *.stackdump
	rm -f *.o
	rm -f $(TARGET1)
	rm -f $(TARGET2)
	
ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif
