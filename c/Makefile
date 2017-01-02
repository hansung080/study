# Makefile

SRCS=sort.c reverse.c rank.c pyramid.c
OBJS=sort.o reverse.o rank.o pyramid.o

OBJ1=sort.o
OBJ2=reverse.o
OBJ3=rank.o
OBJ4=pyramid.o

TARGET1=sort
TARGET2=reverse
TARGET3=rank
TARGET4=pyramid

CC=gcc

all: dep $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

dep:
	$(CC) -MM $(SRCS) > Dependency.dep

$(OBJS): $(SRCS)
	$(CC) -c $^

$(TARGET1): $(OBJ1)
	$(CC) -o $@ $^

$(TARGET2): $(OBJ2)
	$(CC) -o $@ $^

$(TARGET3): $(OBJ3)
	$(CC) -o $@ $^

$(TARGET4): $(OBJ4)
	$(CC) -o $@ $^

clean:
	rm -f Dependency.dep
	rm -f *.pch
	rm -f *.gch
	rm -f *.stackdump
	rm -f *.o
	rm -f $(TARGET1)
	rm -f $(TARGET2)
	rm -f $(TARGET3)
	rm -f $(TARGET4)

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif

