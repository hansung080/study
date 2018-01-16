# Makefile

SRCS=count_thread.cc count_thread_mutex.cc
OBJS=count_thread.o count_thread_mutex.o
TARGET1=count-thread
TARGET2=count-thread-mutex
CXX=g++

all: $(TARGET1) $(TARGET2) 

dep:
	$(CXX) -MM $(SRCS) > Dependency.dep

$(OBJS): $(SRCS)
	$(CXX) -c $^ -pthread -std=c++11

$(TARGET1): count_thread.o
	$(CXX) -o $@ $^ -lpthread 

$(TARGET2): count_thread_mutex.o
	$(CXX) -o $@ $^ -lpthread 

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

