# Makefile

SRCS=sort.c reverse.c
OBJS=sort.o reverse.o

OBJ1=sort.o
OBJ2=reverse.o

TARGET1=sort
TARGET2=reverse

CC=gcc

all: dep $(TARGET1) $(TARGET2)

dep:
	$(CC) -MM $(SRCS) > Dependency.dep

$(OBJS): $(SRCS)
	$(CC) -c $^

$(TARGET1): $(OBJ1)
	$(CC) -o $@ $^

$(TARGET2): $(OBJ2)
	$(CC) -o $@ $^

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
