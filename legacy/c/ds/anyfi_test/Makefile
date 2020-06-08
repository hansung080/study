# Makefile

SRCS=Main.c ArrayList.c UnitTest.c Utility.c Person.c HashMap.c LinkedList.c
OBJS=Main.o ArrayList.o UnitTest.o Utility.o Person.o HashMap.o LinkedList.o
TARGET=anyfi-test
CC=gcc

all:dep $(TARGET)

dep:
	$(CC) -MM $(SRCS) > Dependency.dep
	
$(OBJS): $(SRCS)
	$(CC) -c $^

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lpthread
	
clean:
	rm -f Dependency.dep
	rm -f *.pch
	rm -f *.gch
	rm -f *.stackdump
	rm -f *.o
	rm -f $(TARGET)
	
ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif

