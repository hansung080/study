# Makefile

SRCS=echo_server.c echo_client.c
OBJS=echo_server.o echo_client.o
TARGET1=echo-server
TARGET2=echo-client
CC=gcc

all: dep $(TARGET1) $(TARGET2)

dep:
	$(CC) -MM $(SRCS) > Dependency.dep

$(OBJS): $(SRCS)
	$(CC) -c $^

$(TARGET1): echo_server.o
	$(CC) -o $@ $^

$(TARGET2): echo_client.o
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
