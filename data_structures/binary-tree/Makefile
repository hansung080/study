# Makefile

SRCS=binary_tree.c main.c
OBJS=binary_tree.o main.o
TARGET=binary-tree
CC=gcc

all: dep $(TARGET)

dep:
	$(CC) -MM $(SRCS) > dependencies.dep

$(OBJS): $(SRCS)
	$(CC) -c $^

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f dependencies.dep
	rm -f *.pch
	rm -f *.gch
	rm -f *.stackdump
	rm -f *.o
	rm -f $(TARGET)

ifeq (dependencies.dep, $(wildcard dependencies.dep))
include dependencies.dep
endif
