# Makefile

SRCS=count_thread.cc
OBJS=count_thread.o
TARGET1=count-thread
CXX=g++

all: $(TARGET1) 

dep:
	$(CXX) -MM $(SRCS) > Dependency.dep

$(OBJS): $(SRCS)
	$(CXX) -c $^ -pthread -std=c++11

$(TARGET1): count_thread.o
	$(CXX) -o $@ $^ -lpthread

clean:
	rm -f Dependency.dep
	rm -f *.pch
	rm -f *.gch
	rm -f *.stackdump
	rm -f *.o
	rm -f $(TARGET1)
	
ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif

